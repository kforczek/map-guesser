#include "game/game_window.h"

#include <QFrame>
#include <QStackedLayout>
#include <QMessageBox>

#include "db/location_pool.h"
#include "game/error_message.h"
#include "game/randomizer.h"
#include "game/results.h"
#include "google/coverage.h"

namespace
{

constexpr short int PAGE_START = 0;
constexpr short int PAGE_STREET_VIEW = 1;
constexpr short int PAGE_ROUND_RESULTS = 2;

}

namespace game
{

GameWindow::GameWindow(db::LocationPool locPool)
    : m_locPool(std::move(locPool))
    , m_layout(this)
    , m_startPage(this)
    , m_streetViewPage(this, m_locPool.center())
    , m_roundResultsPage(this, m_locPool.center())
    , m_escShortcut(QKeySequence(Qt::Key_Escape), this)
    , m_f11Shortcut(QKeySequence(Qt::Key_F11), this)
{
    setLayout(&m_layout);

    setMinimumSize(1000, 800);
    setWindowTitle("Map Guesser");
    setWindowFlag(Qt::Window, true);

    m_layout.addWidget(&m_startPage);
    m_layout.addWidget(&m_streetViewPage);
    m_layout.addWidget(&m_roundResultsPage);

    connect(&m_startPage, &pages::StartPage::singlePlayerButtonClicked, this, &GameWindow::onSinglePlayerSelected);
    connect(&m_streetViewPage, &pages::StreetViewPage::guessMade, this, &GameWindow::onGuessMade);
    connect(&m_roundResultsPage, &pages::RoundResultsPage::continueButtonClicked, this, &GameWindow::onContinueButtonClicked);

    connect(&m_escShortcut, &QShortcut::activated, [this]() { toggleFullScreen(false); });
    connect(&m_f11Shortcut, &QShortcut::activated, [this]() { toggleFullScreen(); });
}

void GameWindow::startNextRound()
{
    std::optional<geo::Location> location;
    while (!location)
    {
        try
        {
            location = game::GetRandomStreetViewPoint(m_locPool);
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

void GameWindow::toggleFullScreen(std::optional<bool> fullScreen /*= std::nullopt*/)
{
    if (!fullScreen)
        fullScreen = !isFullScreen();

    if (*fullScreen)
        showFullScreen();
    else
        showNormal();
}

void GameWindow::onSinglePlayerSelected()
{
    startNextRound();
}

void GameWindow::onGuessMade(const geo::Location& guessedLocation)
{
    const geo::Location& actualLocation = m_streetViewPage.getStreetViewLocation();
    const RoundResults roundResults{m_locPool, actualLocation, guessedLocation};

    m_roundResultsPage.setActualLocation(actualLocation);
    m_roundResultsPage.setGuessedLocation(guessedLocation);
    m_roundResultsPage.setInfo(roundResults);

    m_layout.setCurrentIndex(PAGE_ROUND_RESULTS);
}

void GameWindow::onContinueButtonClicked()
{
    startNextRound();
}

}
