#pragma once
#include <qboxlayout.h>
#include <QWidget>
#include <QPushButton>

namespace ui::widgets
{

class StartPageBottomBar final : public QWidget
{
    Q_OBJECT
public:
    explicit StartPageBottomBar(QWidget* parent);

signals:
    void settingsButtonClicked();
    void mapEditorButtonClicked();

private:
    QHBoxLayout m_layout;

    QPushButton m_settingsButton;
    QSpacerItem m_spacer;
    QPushButton m_mapEditorButton;
};

}
