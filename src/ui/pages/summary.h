#pragma once
#include <QFrame>

class QLabel;
class QTableWidget;
class QPushButton;

namespace game
{
struct RoundResults;
}

namespace ui::google
{
class DistanceMap;
}

namespace ui::pages
{

class SummaryPage final : public QFrame
{
    Q_OBJECT
public:
    using TLeaderboard = std::vector</*playerName*/ std::string>;

    explicit SummaryPage(QWidget* parent);
    void setData(const TLeaderboard& leaderboard, const std::vector<game::RoundResults>& roundsHistory, int initialPoints);

signals:
    void closePage();

private /*fields*/:
    QLabel* m_summaryLabel = nullptr;
    QTableWidget* m_leaderboardTable = nullptr;

    google::DistanceMap* m_distanceMap = nullptr;
    QPushButton* m_showPrevRoundButton = nullptr;
    QPushButton* m_showNextRoundButton = nullptr;

    const std::vector<game::RoundResults>* m_roundsHistory = nullptr;
    size_t m_currDisplayedRoundIdx = 0;

    QPushButton* m_finishButton = nullptr;

private slots:
    void onShowPrevRoundButtonClicked();
    void onShowNextRoundButtonClicked();

private /*methods*/:
    void resizeLeaderboardTable(const TLeaderboard& leaderboard);
    void updateLeaderboardTable(const TLeaderboard& leaderboard, int initialPoints);
    void updateSummaryLabel(const TLeaderboard& leaderboard, int initialPoints);
    void updateDistanceMap();
    void updateNavigationButtons();

    int getFinalScore(const std::string& player, int initialPoints) const;
    int getWinnersCount(const TLeaderboard& leaderboard) const;
};

}
