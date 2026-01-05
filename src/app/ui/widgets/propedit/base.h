#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QWidget>

class QWidget;

namespace app::ui::widgets::propedit
{

class PropertyEditor : public QWidget
{
public:
    explicit PropertyEditor(QWidget* parent, const QString& propertyName);

protected:
    void addToLayout(QWidget& widget, Qt::Alignment alignment = Qt::AlignLeft);

private:
    QHBoxLayout m_layout;
    QLabel m_label;
};

}
