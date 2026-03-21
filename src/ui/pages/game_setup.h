#pragma once
#include <QFrame>
#include <QPushButton>
#include "game/params.h"
#include "geo/map.h"
#include "planar/map.h"
#include "util/consumable.h"

namespace ui::widgets
{
class MapPropertyEditor;
class PositiveNumberPropertyEditor;
}

// ####################################################################

namespace ui::pages
{

class GameSetupPage final : public QFrame
{
    Q_OBJECT
public:
    explicit GameSetupPage(QWidget* parent);

signals:
    void startGame(util::consumable<game::Params> gameParams, const geo::Point& centerPoint);

private:
    widgets::MapPropertyEditor* m_propMap = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propRoundsCnt = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propMaxRoundPoints = nullptr;

    QPushButton* m_startGameButton = nullptr;

private slots:
    void onStartGameButtonClicked();
};

}
