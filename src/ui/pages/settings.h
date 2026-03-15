#pragma once
#include <QFrame>

#include "user/settings.h"

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
    explicit SettingsPage(QWidget* parent);

    void reloadData();

signals:
    void closePage();

private /*fields*/:
    widgets::PositiveNumberPropertyEditor* m_propApiStreetViewLimit = nullptr;
    widgets::PositiveNumberPropertyEditor* m_propApiMapsLimit = nullptr;

private slots:
    void onApiUsageInfoButtonClicked();
    void onCloseButtonClicked();
    void onResetToDefaultsButtonClicked();

private /*methods*/:
    user::settings::Values collectPageData();
    void setPageData(const user::settings::Values& data);

    bool handleSave();
    bool handleDiscardQuestion();
};

}
