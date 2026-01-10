#pragma once
#include <QWidget>

#include "geo/map.h"

class QLineEdit;
class QSpinBox;

namespace ui::widgets
{

class MapPropertyEditor final : public QWidget
{
    Q_OBJECT
public:
    explicit MapPropertyEditor(QWidget* parent);

    geo::Map getValue() const;

private:
    QLineEdit* m_valueEdit = nullptr;

private slots:
    void onBrowseButtonClicked();
};

// ########################################################################################

class PositiveNumberPropertyEditor final : public QWidget
{
public:
    struct Values;

    explicit PositiveNumberPropertyEditor(QWidget* parent, const QString& propertyName, const Values& values);
    unsigned int getValue() const;

private:
    QSpinBox* m_valueEdit = nullptr;
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
        if (minValue < 0)
            throw std::invalid_argument("minValue must be >= 0");

        if (minValue > initialValue)
            throw std::invalid_argument("minValue must be <= than initialValue");

        if (initialValue > maxValue)
            throw std::invalid_argument("initialValue must be <= than maxValue");
    };
};

}
