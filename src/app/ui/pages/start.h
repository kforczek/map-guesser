#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QPushButton>

namespace app::ui::pages
{

class StartPage final : public QFrame
{
    Q_OBJECT
public:
    explicit StartPage(QWidget* parent);

signals:
    void singlePlayerButtonClicked();
    void mapEditorButtonClicked();

private /*fields*/:
    QVBoxLayout m_layout;

    QPushButton m_singlePlayerButton;
    QPushButton m_multiPlayerButton;
    QPushButton m_mapEditorButton;
};

}
