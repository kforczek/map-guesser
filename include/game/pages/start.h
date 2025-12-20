#pragma once
#include <qboxlayout.h>
#include <QFrame>
#include <QPushButton>

namespace game::pages
{

class StartPage : public QFrame
{
    Q_OBJECT
public:
    explicit StartPage(QWidget* parent);

signals:
    void singlePlayerButtonClicked();

private:
    QVBoxLayout m_layout;

    QPushButton m_singlePlayerButton;
    QPushButton m_multiPlayerButton;
    QPushButton m_mapEditorButton;

private slots:
    void onSinglePlayerButtonClicked();
    //void onMultiPlayerButtonClicked();
    //void onMapEditorButtonClicked();
};

}
