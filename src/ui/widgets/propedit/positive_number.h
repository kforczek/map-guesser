#pragma once
#include <QSpinBox>

#include "base.h"

namespace ui::widgets::propedit
{

class PositiveNumberPropertyEditor final : public PropertyEditor
{
public:
    explicit PositiveNumberPropertyEditor(QWidget* parent, const QString& propertyName, unsigned int initialValue = 0);

    unsigned int getValue() const;

private:
    QSpinBox m_valueEdit;
};

}
