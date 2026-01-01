#include "app/main_window.h"

#include <QFrame>
#include <QStackedLayout>
#include <QMessageBox>

#include "app/error_message.h"
#include "app/random_point.h"
#include "app/results.h"
#include "google/coverage.h"

namespace
{

// TODO: use page ptrs instead
constexpr short int PAGE_START = 0;
constexpr short int PAGE_GAME_SETUP = 1;
constexpr short int PAGE_STREET_VIEW = 2;
constexpr short int PAGE_ROUND_RESULTS = 3;
constexpr short int PAGE_MAP_EDITOR = 4;

}

namespace app
{

MainWindow::MainWindow()
    : m_layout(this)
    , m_startPage(this)
    , m_gameSetupPage(this)
    , m_streetViewPage(this)
    , m_roundResultsPage(this)
    , m_mapEditorPage(this)
    , m_escShortcut(QKeySequence(Qt::Key_Escape), this)
    , m_f11Shortcut(QKeySequence(Qt::Key_F11), this)
{
    initWindowProperties();
    initLayoutPages();
    initConnections();
}

void MainWindow::initWindowProperties()
{
    setLayout(&m_layout);

    setMinimumSize(1000, 800);
    setWindowTitle("Map Guesser");
    setWindowFlag(Qt::Window, true);
}

void MainWindow::initLayoutPages()
{
    m_layout.addWidget(&m_startPage);
    m_layout.addWidget(&m_gameSetupPage);
    m_layout.addWidget(&m_streetViewPage);
    m_layout.addWidget(&m_roundResultsPage);
    m_layout.addWidget(&m_mapEditorPage);
}

void MainWindow::initConnections()
{
    connect(&m_startPage, &ui::pages::StartPage::singlePlayerButtonClicked, this, &MainWindow::onSinglePlayerRequested);
    connect(&m_startPage, &ui::pages::StartPage::mapEditorButtonClicked, this, &MainWindow::onMapEditorRequested);

    connect(&m_gameSetupPage, &ui::pages::GameSetupPage::startGame, this, &MainWindow::onStartGameRequested);

    connect(&m_mapEditorPage, &ui::pages::MapEditorPage::closePage, this, &MainWindow::onStartPageRequested);

    connect(&m_streetViewPage, &ui::pages::StreetViewPage::guessMade, this, &MainWindow::onGuessMade);
    connect(&m_roundResultsPage, &ui::pages::RoundResultsPage::continueButtonClicked, [this](){ startNextRound(); });

    connect(&m_escShortcut, &QShortcut::activated, [this]() { toggleFullScreen(false); });
    connect(&m_f11Shortcut, &QShortcut::activated, [this]() { toggleFullScreen(); });
}

void MainWindow::startNextRound()
{
    assert(m_gameSession);

    std::optional<geo::Point> location;
    while (!location)
    {
        try
        {
            location = app::GetRandomStreetViewPoint(m_gameSession->params().projectedMap);
        }
        catch (std::runtime_error& err)
        {
            const auto decision = err::ShowErrorMessage(this, err.what());
            if (decision == err::UserDecision::Abort)
                exit(1);
        }
    }

    m_streetViewPage.startNewRound(*location);
    m_layout.setCurrentIndex(PAGE_STREET_VIEW);
}

void MainWindow::toggleFullScreen(std::optional<bool> fullScreen /*= std::nullopt*/)
{
    if (!fullScreen)
        fullScreen = !isFullScreen();

    if (*fullScreen)
        showFullScreen();
    else
        showNormal();
}

void MainWindow::onStartPageRequested()
{
    m_layout.setCurrentIndex(PAGE_START);
}

void MainWindow::onSinglePlayerRequested()
{
    m_layout.setCurrentIndex(PAGE_GAME_SETUP);
}

void MainWindow::onMapEditorRequested()
{
    m_layout.setCurrentIndex(PAGE_MAP_EDITOR);
}

void MainWindow::onStartGameRequested(util::Consumable<game::Params> gameParams)
{
    m_gameSession = game::Session{gameParams.consume()};

    const geo::Point& centerPoint = m_gameSession->params().geoCenter;

    m_streetViewPage.setCenter(centerPoint);
    m_roundResultsPage.setCenter(centerPoint);

    startNextRound();
}

// TODO: maybe receive a signal with RoundResults
void MainWindow::onGuessMade(const geo::Point& guessedLocation)
{
    const geo::Point& actualLocation = m_streetViewPage.getStreetViewLocation();
    const RoundResults roundResults{actualLocation, guessedLocation};

    m_roundResultsPage.setActualLocation(actualLocation);
    m_roundResultsPage.setGuessedLocation(guessedLocation);
    m_roundResultsPage.setInfo(roundResults);

    m_layout.setCurrentIndex(PAGE_ROUND_RESULTS);
}

}
