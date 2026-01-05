#pragma once
#include <QLineEdit>
#include <QPushButton>

#include "base.h"
#include "geo/map.h"

class QWidget;

namespace ui::widgets::propedit
{

class MapPropertyEditor final : public PropertyEditor
{
    Q_OBJECT
public:
    explicit MapPropertyEditor(QWidget* parent);

    geo::Map getValue() const;

private:
    QLineEdit m_valueEdit;
    QPushButton m_browseButton;

private slots:
    void onBrowseButtonClicked();
};

}
