#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QPushButton>

#include "ui/widgets/start_page_bottom_bar.h"

namespace ui::pages
{

class StartPage final : public QFrame
{
    Q_OBJECT
public:
    explicit StartPage(QWidget* parent);

signals:
    void singlePlayerRequested();
    void mapEditorRequested();

private /*fields*/:
    QVBoxLayout m_layout;

    QPushButton m_singlePlayerButton;
    QPushButton m_multiPlayerButton;

    widgets::StartPageBottomBar m_bottomBar;
};

}
