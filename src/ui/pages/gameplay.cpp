#include "ui/pages/gameplay.h"

#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <qstyle.h>

#include "ui/google/interactive_map.h"
#include "ui/google/streetview.h"

namespace
{

constexpr int mapHeightFromWidth(const int mapWidth)
{
    return mapWidth * 3 / 4;
}

constexpr int START_MAP_WIDTH = 400;
constexpr int START_MAP_HEIGHT = mapHeightFromWidth(START_MAP_WIDTH);

constexpr int MAP_X_INCR = 150;
constexpr int MAP_Y_INCR = mapHeightFromWidth(MAP_X_INCR);

constexpr double MIN_MAP_WIDTH_RATIO = 2.0 / 10.0;
constexpr double MAX_MAP_WIDTH_RATIO = 6.0 / 10.0;

constexpr QSize LEFT_INFO_BOX_SIZE_NO_TIMER{ 220, 60 };
constexpr QSize LEFT_INFO_BOX_SIZE_WITH_TIMER{ 220, 100 };

// ##############################################################################

QString formatRoundInfo(unsigned int roundNum, unsigned int roundsCnt)
{
    static const QString FORMAT = "Round %1 of %2";
    return FORMAT
            .arg(QString::number(roundNum))
            .arg(QString::number(roundsCnt));
}

QString formatTimerInfo(unsigned int currTimeSecs)
{
    const unsigned int minutes = currTimeSecs / 60;
    const unsigned int seconds = currTimeSecs - (minutes * 60);

    static const QString FORMAT = "%1:%2";
    return FORMAT
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

// ##############################################################################

}

namespace ui::pages
{

// ##############################################################################

// ReSharper disable CppMemberFunctionMayBeConst

GameplayPage::GameplayPage(QWidget* parent)
    : QFrame(parent) { }

const geo::Point& GameplayPage::getStreetViewLocation() const
{
    if (!m_streetView)
    {
        assert(!"Street View not initialized yet");

        static const geo::Point emptyPoint;
        return emptyPoint;
    }

    return m_streetView->getLocation();
}

void GameplayPage::prepareNewGame(unsigned int roundsCnt, QTime roundTimeLimit)
{
    ensureInitialized();

    m_currRoundNumber = 0;
    m_roundsCnt = roundsCnt;

    m_roundTimeLimit = QTime{0, 0}.secsTo(roundTimeLimit);
    if (m_roundTimeLimit > 0)
    {
        m_timerInfoLabel->setVisible(true);
        m_leftInfoBox->setFixedSize(LEFT_INFO_BOX_SIZE_WITH_TIMER);
    }
    else
    {
        m_timerInfoLabel->setVisible(false);
        m_leftInfoBox->setFixedSize(LEFT_INFO_BOX_SIZE_NO_TIMER);
    }
}

void GameplayPage::startNextRound(const geo::Point& location)
{
    ++m_currRoundNumber;
    m_roundInfoLabel->setText(formatRoundInfo(m_currRoundNumber, m_roundsCnt));

    m_currRoundTimeLeft = m_roundTimeLimit;

    m_streetView->setLocation(location);
    m_interactiveMap->removeLocationMarker();
    m_guessButton->setEnabled(false);

    if (m_roundTimeLimit > 0)
    {
        setTimerLabelUrgency("normal");
        m_roundTimer->start(1000);
        m_timerInfoLabel->setVisible(true);
    }
}

void GameplayPage::setMapCenter(const geo::Point& center)
{
    m_mapCenter = center;

    if (m_interactiveMap)
        m_interactiveMap->setCenter(m_mapCenter);
}

void GameplayPage::showEvent(QShowEvent *event)
{
    updateMapRatios();
    QFrame::showEvent(event);
}

void GameplayPage::resizeEvent(QResizeEvent* event)
{
    QFrame::resizeEvent(event);
    resize();
}

void GameplayPage::ensureInitialized()
{
    if (m_initialized)
        return;

    setContentsMargins(0, 0, 0, 0);

    setupMembers();
    setupGeometries();
    setupConnections();

    m_initialized = true;
    resize();
}

void GameplayPage::setupMembers()
{
    m_streetView = new google::StreetView(this);
    m_interactiveMap = new google::InteractiveMap(this);

    m_roundTimer = new QTimer(this);

    m_leftInfoBox = new QWidget(this);

    m_roundInfoLabel = new QLabel(m_leftInfoBox);
    m_roundInfoLabel->setObjectName("roundInfo");

    m_timerInfoLabel = new QLabel(m_leftInfoBox);
    m_timerInfoLabel->setObjectName("timerInfo");

    m_returnToStartButton = new QPushButton("Return to start", this);
    m_guessButton = new QPushButton("Guess", this);
    m_shrinkMapButton = new QPushButton("-", this);
    m_enlargeMapButton = new QPushButton("+", this);

    m_guessButton->setEnabled(false);

    if (m_mapCenter != geo::Point{})
        m_interactiveMap->setCenter(m_mapCenter);
}

void GameplayPage::setupGeometries()
{
    // TODO: necessary? resize() is called in the end anyway
    m_streetView->setGeometry(rect());
    m_interactiveMap->setFixedSize(START_MAP_WIDTH, START_MAP_HEIGHT);
    m_guessButton->setMinimumSize(150, 40);
    m_returnToStartButton->setMinimumSize(150, 40);
    m_shrinkMapButton->setFixedSize(30, 30);
    m_enlargeMapButton->setFixedSize(30, 30);

    m_leftInfoBox->move(10, 10);

    m_roundInfoLabel->setFixedSize(220, 40);
    m_roundInfoLabel->move(0, 10);
    m_roundInfoLabel->setAlignment(Qt::AlignCenter);
    m_roundInfoLabel->setText(formatRoundInfo(m_currRoundNumber, m_roundsCnt));

    m_timerInfoLabel->setFixedSize(220, 40);
    m_timerInfoLabel->move(0, 50);
    m_timerInfoLabel->setAlignment(Qt::AlignCenter);
    m_timerInfoLabel->setVisible(false);
}

void GameplayPage::setupConnections()
{
    connect(m_interactiveMap, &google::InteractiveMap::guessMarkerPlaced, this, &GameplayPage::onGuessMarkerPlaced);
    connect(m_roundTimer, &QTimer::timeout, this, &GameplayPage::onTimerTick);
    connect(m_guessButton, &QPushButton::clicked, this, &GameplayPage::onGuessButtonClicked);
    connect(m_returnToStartButton, &QPushButton::clicked, this, &GameplayPage::onReturnToStartButtonClicked);
    connect(m_shrinkMapButton, &QPushButton::clicked, this, &GameplayPage::onShrinkMapButtonClicked);
    connect(m_enlargeMapButton, &QPushButton::clicked, this, &GameplayPage::onEnlargeMapButtonClicked);
}

void GameplayPage::resize()
{
    resizeStreetView();
    resizeAndMoveMap();
    moveMapSizeButtons();
    moveFunctionalButtons();
}

void GameplayPage::resizeStreetView()
{
    if (m_streetView)
        m_streetView->resize(width(), height());
}

void GameplayPage::resizeAndMoveMap(int newWidth /*= 0*/, int newHeight /*= 0*/)
{
    if (!m_initialized)
        return;

    const bool isAutoGeneratedSize = newWidth == 0 || newHeight == 0;
    if (isAutoGeneratedSize)
    {
        newWidth = static_cast<int>(m_mapToWindowWidthRatio * width());
        newHeight = mapHeightFromWidth(newWidth);
    }

    m_interactiveMap->setFixedSize(newWidth, newHeight);

    m_interactiveMap->move(width() - m_interactiveMap->width() - 10,
                        height() - m_interactiveMap->height() - 50);

    if (!isAutoGeneratedSize)
        updateMapRatios();
}

void GameplayPage::moveMapSizeButtons()
{
    if (!m_initialized)
        return;

    m_enlargeMapButton->move(
        m_interactiveMap->x() + m_interactiveMap->width() - m_enlargeMapButton->width() - 5,
        m_interactiveMap->y() + m_interactiveMap->height() - m_enlargeMapButton->height() - 5
    );

    m_shrinkMapButton->move(
        m_enlargeMapButton->x() - m_shrinkMapButton->width() - 5,
        m_enlargeMapButton->y()
    );
}

void GameplayPage::moveFunctionalButtons()
{
    if (!m_initialized)
        return;

    m_guessButton->move(
        m_interactiveMap->x() + m_interactiveMap->width() - m_guessButton->width(),
        m_interactiveMap->y() + m_interactiveMap->height() + 5
    );

    m_returnToStartButton->move(
        m_guessButton->x() - m_returnToStartButton->width() - 10,
        m_guessButton->y()
    );
}

void GameplayPage::updateMapRatios()
{
    if (!m_initialized)
        return;

    const double mapWidth = m_interactiveMap->width() != 0 ? m_interactiveMap->width() : START_MAP_WIDTH;
    m_mapToWindowWidthRatio = mapWidth / width();
}

void GameplayPage::setMapSizeButtonsEnabledState()
{
    const bool canShrink = m_mapToWindowWidthRatio > MIN_MAP_WIDTH_RATIO;
    const bool canEnlarge = m_mapToWindowWidthRatio < MAX_MAP_WIDTH_RATIO;

    m_shrinkMapButton->setEnabled(canShrink);
    m_enlargeMapButton->setEnabled(canEnlarge);
}

void GameplayPage::setTimerLabelUrgency(const QString& urgency)
{
    m_timerInfoLabel->setProperty("urgency", urgency);
    m_timerInfoLabel->style()->unpolish(m_timerInfoLabel);
    m_timerInfoLabel->style()->polish(m_timerInfoLabel);
    m_timerInfoLabel->update();
}

void GameplayPage::onGuessMarkerPlaced()
{
    m_guessButton->setEnabled(true);
}

void GameplayPage::onTimerTick()
{
    --m_currRoundTimeLeft;
    m_timerInfoLabel->setText(formatTimerInfo(m_currRoundTimeLeft));

    switch (m_currRoundTimeLeft)
    {
        case 15:
            setTimerLabelUrgency("warning");
            break;
        case 5:
            setTimerLabelUrgency("critical");
            break;
        case 0:
            m_roundTimer->stop();
            emit playerFinishedRound(m_interactiveMap->currLocation());
            break;
        default:
            break;
    }
}

void GameplayPage::onGuessButtonClicked()
{
    m_roundTimer->stop();
    emit playerFinishedRound(m_interactiveMap->currLocation());
}

void GameplayPage::onReturnToStartButtonClicked()
{
    m_streetView->returnToStart();
}

void GameplayPage::onShrinkMapButtonClicked()
{
    const auto newWidth = m_interactiveMap->width() - MAP_X_INCR;
    const auto newHeight = m_interactiveMap->height() - MAP_Y_INCR;

    resizeAndMoveMap(newWidth,  newHeight);
    setMapSizeButtonsEnabledState();
}

void GameplayPage::onEnlargeMapButtonClicked()
{
    const auto newWidth = m_interactiveMap->width() + MAP_X_INCR;
    const auto newHeight = m_interactiveMap->height() + MAP_Y_INCR;

    resizeAndMoveMap(newWidth,  newHeight);
    setMapSizeButtonsEnabledState();
}

// ReSharper restore CppMemberFunctionMayBeConst

}