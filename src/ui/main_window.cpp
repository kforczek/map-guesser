#include "main_window.h"

#include <QStackedLayout>
#include <QMessageBox>
#include <QShortcut>

#include "pages/game_setup.h"
#include "pages/start.h"
#include "pages/round_results.h"
#include "pages/gameplay.h"
#include "pages/summary.h"
#include "pages/map_editor.h"

#include "game/round_results.h"

namespace ui
{

MainWindow::MainWindow()
    : m_layout(new QStackedLayout(this))
    , m_startPage(new pages::StartPage(this))
    , m_gameSetupPage(new pages::GameSetupPage(this))
    , m_gameplayPage(new pages::GameplayPage(this))
    , m_roundResultsPage(new pages::RoundResultsPage(this))
    , m_summaryPage(new pages::SummaryPage(this))
    , m_mapEditorPage(new pages::MapEditorPage(this))
    , m_escShortcut(new QShortcut(QKeySequence(Qt::Key_Escape), this))
    , m_f11Shortcut(new QShortcut(QKeySequence(Qt::Key_F11), this))
{
    initWindowProperties();
    initLayoutPages();
    initConnections();
}

void MainWindow::setMapCenter(const geo::Point& centerPoint)
{
    m_gameplayPage->setCenter(centerPoint);
    m_roundResultsPage->setCenter(centerPoint);
}

void MainWindow::startNextRound(const geo::Point& location)
{
    m_gameplayPage->startNextRound(location);
    m_layout->setCurrentWidget(m_gameplayPage);
}

void MainWindow::showPlayerGuessed(const std::string& playerName)
{
    // TODO [multiplayer]: highlight that a player has guessed
}

void MainWindow::showRoundResults(const game::RoundResults& roundResults, bool isGameOver)
{
    using TContinueButtonType = pages::RoundResultsPage::EContinueButtonType;

    m_roundResultsPage->setData(roundResults);
    m_roundResultsPage->setContinueButtonType(isGameOver ? TContinueButtonType::Summary : TContinueButtonType::NextRound);

    m_layout->setCurrentWidget(m_roundResultsPage);
}

void MainWindow::showGameSummary(
    const std::vector<std::string>& leaderboard,
    const std::vector<game::RoundResults>& roundsHistory,
    int initialPoints
)
{
    m_summaryPage->setData(leaderboard, roundsHistory, initialPoints);
    m_layout->setCurrentWidget(m_summaryPage);
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
    setLayout(m_layout);

    setMinimumSize(1000, 800);
    setWindowTitle("Map Guesser");
    setWindowFlag(Qt::Window, true);
}

void MainWindow::initLayoutPages()
{
    m_layout->addWidget(m_startPage);
    m_layout->addWidget(m_gameSetupPage);
    m_layout->addWidget(m_gameplayPage);
    m_layout->addWidget(m_roundResultsPage);
    m_layout->addWidget(m_summaryPage);
    m_layout->addWidget(m_mapEditorPage);
}

void MainWindow::initConnections()
{
    connect(m_startPage, &pages::StartPage::singlePlayerRequested, this, &MainWindow::onSinglePlayerRequested);
    connect(m_startPage, &pages::StartPage::mapEditorRequested, this, &MainWindow::onMapEditorRequested);

    connect(m_gameSetupPage, &pages::GameSetupPage::startGame, this, &MainWindow::startGameRequested);
    connect(m_gameplayPage, &pages::GameplayPage::guessMade, this, &MainWindow::guessSubmitted);

    connect(m_roundResultsPage, &pages::RoundResultsPage::closePage, this, &MainWindow::nextRoundRequested);
    connect(m_summaryPage, &pages::SummaryPage::closePage, this, &MainWindow::onStartPageRequested);
    connect(m_mapEditorPage, &pages::MapEditorPage::closePage, this, &MainWindow::onStartPageRequested);

    connect(m_escShortcut, &QShortcut::activated, [this]() { toggleFullScreen(false); });
    connect(m_f11Shortcut, &QShortcut::activated, [this]() { toggleFullScreen(); });
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
    m_layout->setCurrentWidget(m_startPage);
}

void MainWindow::onSinglePlayerRequested()
{
    m_layout->setCurrentWidget(m_gameSetupPage);
}

void MainWindow::onMapEditorRequested()
{
    m_layout->setCurrentWidget(m_mapEditorPage);
}

}
