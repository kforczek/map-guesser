#include "summary.h"

#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QStringList>
#include <ranges>
#include <QStyledItemDelegate>
#include <QPainter>

#include "game/round_results.h"
#include "ui/google/distance_map.h"

namespace
{

// #############################################################################################

class HtmlDelegate final: public QStyledItemDelegate
{
public:
	explicit HtmlDelegate(QObject* parent = nullptr)
		: QStyledItemDelegate(parent) {}

	void paint(QPainter* painter,
			   const QStyleOptionViewItem& option,
			   const QModelIndex& index) const override
	{
		QStyleOptionViewItem opt = option;
		initStyleOption(&opt, index);

		opt.text.clear();
		opt.widget->style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

		QTextDocument doc;
		// Inherit the correct foreground color (respects selection highlight too)
		const QColor color = opt.palette.color(
			opt.state & QStyle::State_Selected ? QPalette::HighlightedText : QPalette::Text);
		doc.setDefaultStyleSheet(QString("body { color: %1; }").arg(color.name()));
		doc.setHtml(QString("<body>%1</body>").arg(index.data(Qt::DisplayRole).toString()));
		doc.setTextWidth(opt.rect.width());

		// Center vertically
		const int docHeight = doc.size().height();
		const int yOffset = (opt.rect.height() - docHeight) / 2;

		painter->save();
		painter->translate(opt.rect.left(), opt.rect.top() + yOffset);
		doc.drawContents(painter);
		painter->restore();
	}

	QSize sizeHint(const QStyleOptionViewItem& option,
				   const QModelIndex& index) const override
	{
		QTextDocument doc;
		doc.setHtml(index.data(Qt::DisplayRole).toString());
		// Don't constrain width here — just get the natural height
		return QSize(doc.idealWidth(), doc.size().height());
	}
};

// #############################################################################################

QStringList createColumnNames(size_t roundsCnt)
{
	QStringList names;
	for (size_t i = 1; i < roundsCnt + 1; ++i)
		names << QString("Round %1").arg(i);

	return names;
}

QStringList createRowNames(const ui::pages::SummaryPage::TLeaderboard& leaderboard)
{
	QStringList names;
	for (const std::string& playerName : leaderboard)
		names << playerName.c_str();

	return names;
}

QString formatCaptionForMultipleWinners(std::ranges::viewable_range auto&& winners)
{
	QString caption = "Winners: ";
	caption += winners.front().c_str();

	for (const std::string& winner : winners)
	{
		caption += ", ";
		caption += winner.c_str();
	}

	return caption;
}

// #############################################################################################

}

namespace ui::pages
{

SummaryPage::SummaryPage(QWidget* parent)
	: QFrame(parent) { }

void SummaryPage::setData(const TLeaderboard& leaderboard, const std::vector<game::RoundResults>& roundsHistory, int initialPoints)
{
	ensureInitialized();

	assert(!roundsHistory.empty());
	m_roundsHistory = &roundsHistory;
	m_currDisplayedRoundIdx = 0;

	updateSummaryLabel(leaderboard, initialPoints);
	updateLeaderboardTable(leaderboard, initialPoints);
	updateDistanceMap();
	updateNavigationButtons();
}

void SummaryPage::onShowPrevRoundButtonClicked()
{
	--m_currDisplayedRoundIdx;

	updateDistanceMap();
	updateNavigationButtons();
}
void SummaryPage::onShowNextRoundButtonClicked()
{
	++m_currDisplayedRoundIdx;

	updateDistanceMap();
	updateNavigationButtons();
}

void SummaryPage::ensureInitialized()
{
	if (m_initialized)
		return;

	m_summaryLabel = new QLabel(this);
	m_leaderboardTable = new QTableWidget(this);
	m_distanceMap = new google::DistanceMap(this);
	m_showPrevRoundButton = new QPushButton("<-", this);
	m_showNextRoundButton = new QPushButton("->", this);
	m_finishButton = new QPushButton("Finish", this);

	m_leaderboardTable->setItemDelegate(new HtmlDelegate(m_leaderboardTable));
	m_leaderboardTable->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	auto* leaderboardTab = new QFrame(this);
	auto* leaderboardTabLayout = new QVBoxLayout(leaderboardTab);
	leaderboardTab->setLayout(leaderboardTabLayout);
	leaderboardTabLayout->addWidget(m_summaryLabel, 0);
	leaderboardTabLayout->addWidget(m_leaderboardTable, 1);

	auto* roundsTabButtons = new QFrame(this);
	roundsTabButtons->setLayout(new QHBoxLayout(roundsTabButtons));
	roundsTabButtons->layout()->addWidget(m_showPrevRoundButton);
	roundsTabButtons->layout()->addWidget(m_showNextRoundButton);

	auto* roundsTab = new QFrame(this);
	auto* roundsTabLayout = new QVBoxLayout(roundsTab);

	roundsTabLayout->addWidget(m_distanceMap, 1);
	roundsTabLayout->addWidget(roundsTabButtons, 0);
	roundsTab->setLayout(roundsTabLayout);

	auto* tabWidget = new QTabWidget(this);
	tabWidget->addTab(leaderboardTab, "Leaderboard");
	tabWidget->addTab(roundsTab, "Rounds");

	setLayout(new QVBoxLayout(this));
	layout()->addWidget(tabWidget);
	layout()->addWidget(m_finishButton);

	connect(m_showPrevRoundButton, &QPushButton::clicked, this, &SummaryPage::onShowPrevRoundButtonClicked);
	connect(m_showNextRoundButton, &QPushButton::clicked, this, &SummaryPage::onShowNextRoundButtonClicked);
	connect(m_finishButton, &QPushButton::clicked, this, &SummaryPage::closePage);

	m_initialized = true;
}

void SummaryPage::resizeLeaderboardTable(const TLeaderboard& leaderboard)
{
	const QStringList colNames = createColumnNames(m_roundsHistory->size());
	m_leaderboardTable->setColumnCount(colNames.size());
	m_leaderboardTable->setHorizontalHeaderLabels(colNames);

	const QStringList rowNames = createRowNames(leaderboard);
	m_leaderboardTable->setRowCount(rowNames.size());
	m_leaderboardTable->setVerticalHeaderLabels(rowNames);
}

void SummaryPage::updateLeaderboardTable(const TLeaderboard& leaderboard, int initialPoints)
{
	resizeLeaderboardTable(leaderboard);

	for (TLeaderboard::size_type rowIdx = 0; rowIdx < leaderboard.size(); ++rowIdx)
	{
		const std::string& playerName = leaderboard[rowIdx];
		int playerPoints = initialPoints;

		for (std::vector<game::RoundResults>::size_type colIdx = 0; colIdx < m_roundsHistory->size(); ++colIdx)
		{
			const game::RoundResults& roundResult = m_roundsHistory->at(colIdx);
			const game::PlayerRoundResult& playerResult = roundResult.playerResults.at(playerName);

			playerPoints += playerResult.pointsChange;
			QString cellText = QString("<b>%1</b><br>%2")
				.arg(playerResult.pointsChange)
				.arg(playerPoints);

			auto* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, cellText);

			m_leaderboardTable->setItem(rowIdx, colIdx, item);
		}
	}

	m_leaderboardTable->resizeRowsToContents();
	m_leaderboardTable->resizeColumnsToContents();
}

void SummaryPage::updateSummaryLabel(const TLeaderboard& leaderboard, int initialPoints)
{
	const bool isSinglePlayer = leaderboard.size() == 1;

	QString caption;
	if (isSinglePlayer)
	{
		const int totalScore = getFinalScore(*leaderboard.begin(), initialPoints);
		caption = "Total score: " + QString::number(totalScore);
	}
	else
	{
		const int winnersCount = getWinnersCount(leaderboard);
		if (winnersCount == 1) {
			caption = QString::fromStdString(leaderboard.front() + " wins!");
		}
		else {
			caption = formatCaptionForMultipleWinners(leaderboard | std::views::take(winnersCount));
		}
	}

	m_summaryLabel->setText(caption);
}

void SummaryPage::updateDistanceMap()
{
	const game::RoundResults& shownRound = m_roundsHistory->at(m_currDisplayedRoundIdx);

	m_distanceMap->setActualLocation(shownRound.correctLocation);

	// TODO [multiplayer]: show results for all players
	m_distanceMap->setGuessedLocation(shownRound.playerResults.begin()->second.guess);
	m_distanceMap->setDistance(shownRound.playerResults.begin()->second.distanceMeters.value_or(0));
}

void SummaryPage::updateNavigationButtons()
{
	const bool canGoBack = m_currDisplayedRoundIdx > 0;
	m_showPrevRoundButton->setEnabled(canGoBack);

	const bool canGoForward = m_currDisplayedRoundIdx < m_roundsHistory->size() - 1;
	m_showNextRoundButton->setEnabled(canGoForward);
}

int SummaryPage::getFinalScore(const std::string& player, int initialPoints) const
{
	int points = initialPoints;
	for (const game::RoundResults& roundResult : *m_roundsHistory)
		points += roundResult.playerResults.at(player).pointsChange;

	return points;
}

int SummaryPage::getWinnersCount(const TLeaderboard& leaderboard) const
{
	const int winnerScore = getFinalScore(*leaderboard.begin(), 0);

	int winnersCount = 1;
	for (auto it = ++leaderboard.begin(); it != leaderboard.end(); ++it)
	{
		if (getFinalScore(*it, 0) != winnerScore)
			break;

		++winnersCount;
	}

	return winnersCount;
}

	/*
	 *                  KAYEFF WINS!
	 *
	 *---------------------------------------------
	 * player |  round 1  |  round 2  |  round 3  |
	 *---------------------------------------------
	 * kayeff |   -200    |     0     |     0     |
	 *        |   4800    |   4800    |   4800    |
	 * --------------------------------------------
	 * Daniel |    0      |   -2600   |   -6500   |
	 *        |   5000    |    2400   |     0     |
	 *---------------------------------------------
	 */

}