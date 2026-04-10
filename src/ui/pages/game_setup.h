#pragma once
#include <QFrame>
#include <QPushButton>
#include "geo/map.h"
#include "planar/map.h"
#include "util/consumable.h"

namespace ui
{
struct Params;
}

namespace ui::widgets
{
class MapPropertyEditor;
class PositiveNumberPropertyEditor;
class TimePropertyEditor;
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
    void startGame(const Params& params);

private:
    widgets::MapPropertyEditor* m_propMap = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propRoundsCnt = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propMaxRoundPoints = nullptr;
    widgets::TimePropertyEditor* m_propRoundTimeLimit = nullptr;

    QPushButton* m_startGameButton = nullptr;

private slots:
    void onStartGameButtonClicked();
};

}
