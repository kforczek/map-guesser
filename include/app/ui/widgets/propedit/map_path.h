#pragma once
#include <QLineEdit>
#include <QPushButton>

#include "base.h"

class QWidget;

namespace app::ui::widgets::propedit
{

class MapPathPropertyEditor final : public PropertyEditor
{
    Q_OBJECT
public:
    explicit MapPathPropertyEditor(QWidget* parent);

    QString getValue() const;

private:
    QLineEdit m_valueEdit;
    QPushButton m_browseButton;

private slots:
    void onBrowseButtonClicked();
};

}
