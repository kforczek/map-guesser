#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

namespace mapeditor
{

class TopBar final : public QWidget
{
public:
    explicit TopBar(QWidget* parent);

private:
    QHBoxLayout m_layout;

    QLabel m_infoLabel;
    QPushButton m_loadButton;
    QPushButton m_saveAsButton;
};

}
