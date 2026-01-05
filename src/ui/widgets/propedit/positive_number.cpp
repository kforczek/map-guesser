#include "ui/widgets/propedit/positive_number.h"

namespace ui::widgets::propedit
{

PositiveNumberPropertyEditor::PositiveNumberPropertyEditor(QWidget* parent, const QString& propertyName, unsigned int initialValue /* = 0 */)
    : PropertyEditor(parent, propertyName)
    , m_valueEdit(this)
{
    m_valueEdit.setMinimum(0);
    m_valueEdit.setMaximum(1000000);
    m_valueEdit.setValue(static_cast<int>(initialValue));

    addToLayout(m_valueEdit);
    finishInit();
}

unsigned int PositiveNumberPropertyEditor::getValue() const
{
    return m_valueEdit.value();
}

}