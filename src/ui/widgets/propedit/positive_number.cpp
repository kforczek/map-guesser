#include "ui/widgets/propedit/positive_number.h"

namespace ui::widgets::propedit
{

PositiveNumberPropertyEditor::PositiveNumberPropertyEditor(QWidget* parent, const QString& propertyName, const Values& values)
    : PropertyEditor(parent, propertyName)
    , m_valueEdit(this)
{
    m_valueEdit.setMinimum(values.minValue);
    m_valueEdit.setMaximum(values.maxValue);
    m_valueEdit.setValue(values.initialValue);

    addToLayout(m_valueEdit);
    finishInit();
}

unsigned int PositiveNumberPropertyEditor::getValue() const
{
    return m_valueEdit.value();
}

}