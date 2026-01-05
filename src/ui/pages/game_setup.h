#pragma once
#include <QFrame>
#include <QPushButton>

#include "game/params.h"
#include "ui/widgets/propedit/map.h"
#include "ui/widgets/propedit/positive_number.h"
#include "util/consumable.h"

namespace ui::pages
{

class GameSetupPage final : public QFrame
{
    Q_OBJECT
public:
    explicit GameSetupPage(QWidget* parent);

signals:
    void startGame(util::Consumable<game::Params> gameParams);

private:
    QVBoxLayout m_layout;

    widgets::propedit::MapPropertyEditor m_propMap;
    widgets::propedit::PositiveNumberPropertyEditor m_propMaxRoundPoints;

    QPushButton m_startGameButton;

private slots:
    void onStartGameButtonClicked();
};

}
