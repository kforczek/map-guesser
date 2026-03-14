#pragma once
#include <QFrame>

#include "user/settings.h"

namespace ui::api_usage
{
class Counter;
}

namespace ui::widgets
{
class PositiveNumberPropertyEditor;
}

namespace ui::pages
{

class SettingsPage final : public QFrame
{
    Q_OBJECT
public:
    explicit SettingsPage(QWidget* parent, const api_usage::Counter& apiUsageCounter);

    void reloadData();

signals:
    void closePage();

private /*fields*/:
    const api_usage::Counter* m_apiUsageCounter = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propApiStreetViewLimit = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propApiMapsLimit = nullptr;

private slots:
    void onCloseButtonClicked();
    void onApiUsageInfoButtonClicked();

private /*methods*/:
    user::settings::Values collectPageData();

    void handleSave();
};

}
