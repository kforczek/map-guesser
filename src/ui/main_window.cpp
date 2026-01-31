#include "main_window.h"

#include <QFrame>
#include <QStackedLayout>
#include <QMessageBox>

#include "game/round_results.h"

namespace ui
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

void MainWindow::setMapCenter(const geo::Point& centerPoint)
{
    m_streetViewPage.setCenter(centerPoint);
    m_roundResultsPage.setCenter(centerPoint);
}

void MainWindow::startNextRound(const geo::Point& location)
{
    m_streetViewPage.startNextRound(location);
    m_layout.setCurrentWidget(&m_streetViewPage);
}

void MainWindow::showPlayerGuessed(const std::string& playerName)
{
    // TODO [multiplayer]: highlight that a player has guessed
}

void MainWindow::showRoundResults(const game::RoundResults& roundResults)
{
    m_roundResultsPage.setData(roundResults);
    m_layout.setCurrentWidget(&m_roundResultsPage);
}

QMessageBox::StandardButton MainWindow::showErrorMessage(QString errDetails)
{
    if (!errDetails.endsWith('.'))
        errDetails += '.';

    return QMessageBox::critical(
        this,
        "MapGuesser Error",
        errDetails,
        QMessageBox::Retry | QMessageBox::Abort,
        QMessageBox::Retry
    );
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
    connect(&m_startPage, &pages::StartPage::singlePlayerRequested, this, &MainWindow::onSinglePlayerRequested);
    connect(&m_startPage, &pages::StartPage::mapEditorRequested, this, &MainWindow::onMapEditorRequested);

    connect(&m_gameSetupPage, &pages::GameSetupPage::startGame, this, &MainWindow::startGameRequested);

    connect(&m_mapEditorPage, &pages::MapEditorPage::closePage, this, &MainWindow::onStartPageRequested);

    connect(&m_streetViewPage, &pages::StreetViewPage::guessMade, this, &MainWindow::guessSubmitted);
    connect(&m_roundResultsPage, &pages::RoundResultsPage::continueButtonClicked, this, &MainWindow::nextRoundRequested);

    connect(&m_escShortcut, &QShortcut::activated, [this]() { toggleFullScreen(false); });
    connect(&m_f11Shortcut, &QShortcut::activated, [this]() { toggleFullScreen(); });
}

void MainWindow::toggleFullScreen(std::optional<bool> fullScreen /*= std::nullopt*/)
{
    if (fullScreen.value_or(!isFullScreen()))
        showFullScreen();
    else
        showNormal();
}

void MainWindow::onStartPageRequested()
{
    m_layout.setCurrentWidget(&m_startPage);
}

void MainWindow::onSinglePlayerRequested()
{
    m_layout.setCurrentWidget(&m_gameSetupPage);
}

void MainWindow::onMapEditorRequested()
{
    m_layout.setCurrentWidget(&m_mapEditorPage);
}

}
