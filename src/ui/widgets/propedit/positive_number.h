#pragma once
#include <QSpinBox>

#include "base.h"

namespace ui::widgets::propedit
{

class PositiveNumberPropertyEditor final : public PropertyEditor
{
public:
    struct Values;

    explicit PositiveNumberPropertyEditor(QWidget* parent, const QString& propertyName, const Values& values);
    unsigned int getValue() const;

private:
    QSpinBox m_valueEdit;
};

// ########################################################################################

struct PositiveNumberPropertyEditor::Values
{
    int minValue = 0;
    int initialValue = 0;
    int maxValue = 0;

    consteval Values(int minValue, int initialValue, int maxValue)
        : minValue(minValue)
        , initialValue(initialValue)
        , maxValue(maxValue)
    {
        if (minValue > initialValue)
            throw std::invalid_argument("minValue must be <= than initialValue");

        if (initialValue > maxValue)
            throw std::invalid_argument("initialValue must be <= than maxValue");
    };
};

}
