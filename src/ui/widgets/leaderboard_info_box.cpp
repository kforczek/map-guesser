#include "leaderboard_info_box.h"
#include "ui/cache/player_data.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFont>
#include <QSizePolicy>

namespace
{

struct PlayerDataScoreComparator
{
    bool operator()(const ui::cache::PlayerData& lhs, const ui::cache::PlayerData& rhs) const
    {
        return lhs.points > rhs.points;
    }
};

}

namespace ui::widgets
{

// #########################################################################

class LeaderboardInfoBox::Row final : public QWidget
{
public:
    explicit Row(QWidget* parent);

    void setData(const cache::PlayerData& playerData);

private:
    QLabel* m_nameLabel = nullptr;
    QLabel* m_scoreLabel = nullptr;
};

LeaderboardInfoBox::Row::Row(QWidget* parent)
    : QWidget(parent)
{
    auto* grid = new QGridLayout(this);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setHorizontalSpacing(8);
    grid->setVerticalSpacing(0);

    m_nameLabel = new QLabel(this);
    m_nameLabel->setObjectName("lbPlayerName");
    m_nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    auto* sep = new QLabel(":", this);
    sep->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    sep->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    m_scoreLabel = new QLabel(this);
    m_scoreLabel->setObjectName("lbPlayerScore");
    m_scoreLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QFont scoreFont = m_scoreLabel->font();
    scoreFont.setBold(true);
    m_scoreLabel->setFont(scoreFont);

    grid->addWidget(m_nameLabel,  0, 0);
    grid->addWidget(sep,     0, 1);
    grid->addWidget(m_scoreLabel, 0, 2);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 0);
    grid->setColumnStretch(2, 1);
}

void LeaderboardInfoBox::Row::setData(const cache::PlayerData& playerData)
{
    m_nameLabel->setText(playerData.name);
    m_scoreLabel->setText(QString::number(playerData.points));
}

// #########################################################################

LeaderboardInfoBox::LeaderboardInfoBox(QWidget* parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
{
    m_layout->setContentsMargins(10, 10, 10, 10);

    auto* headerLabel = new QLabel("Leaderboard", this);
    headerLabel->setObjectName("lbHeader");
    headerLabel->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(headerLabel);
}

void LeaderboardInfoBox::reload()
{
    removeExtraRows();
    createMissingRows();
    updateData();
}

void LeaderboardInfoBox::removeExtraRows()
{
    const size_t playersCnt = cache::GetId2PlayerData().size();
    if (m_rows.size() <= playersCnt)
        return;

    for (std::size_t i = playersCnt; i < m_rows.size(); ++i)
    {
        Row* row = m_rows[i];

        m_layout->removeWidget(row);
        row->deleteLater();
    }

    m_rows.resize(playersCnt);
}

void LeaderboardInfoBox::createMissingRows()
{
    while (m_rows.size() < cache::GetId2PlayerData().size())
    {
        auto* row = new Row(this);
        m_layout->addWidget(row);
        m_rows.push_back(row);
    }
}

void LeaderboardInfoBox::updateData()
{
    auto playersData = cache::GetId2PlayerData();
    assert(playersData.size() == m_rows.size());

    std::ranges::sort(playersData, PlayerDataScoreComparator{});

    for (std::size_t i = 0; i < playersData.size(); ++i)
    {
        m_rows[i]->setData(playersData[i]);
    }
}

}