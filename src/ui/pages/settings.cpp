#include "ui/pages/settings.h"
#include "user/settings.h"

#include <qboxlayout.h>
#include <QMessageBox>
#include <QPushButton>

#include "ui/api_usage/msg.h"
#include "ui/widgets/propedit.h"

namespace
{

constinit ui::widgets::PositiveNumberPropertyEditor::Values API_USAGE_VALS{0, 0, 100'000};

const QString API_STREETVIEW_LIMIT_PROP_NAME = "Street View API limit (0 = tracking disabled)";
const QString API_MAPS_LIMIT_PROP_NAME = "Maps API limit (0 = tracking disabled)";

}

namespace ui::pages
{

SettingsPage::SettingsPage(QWidget* parent)
    : QFrame(parent)
    , m_propApiStreetViewLimit(new widgets::PositiveNumberPropertyEditor(this, API_STREETVIEW_LIMIT_PROP_NAME, API_USAGE_VALS))
    , m_propApiMapsLimit(new widgets::PositiveNumberPropertyEditor(this, API_MAPS_LIMIT_PROP_NAME, API_USAGE_VALS))
{
    auto* layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addStretch(10);
    layout->addWidget(m_propApiStreetViewLimit);
    layout->addWidget(m_propApiMapsLimit);
    layout->addStretch(10);

    auto* apiUsageInfoButton = new QPushButton("API usage info", this);
    auto* closeButton = new QPushButton("Close", this);
    auto* resetToDefaultsButton = new QPushButton("Reset to defaults", this);

    apiUsageInfoButton->setFixedSize(150, 50);
    closeButton->setFixedSize(300, 50);
    resetToDefaultsButton->setFixedSize(150, 50);

    auto* bottomBarLayout = new QHBoxLayout;
    bottomBarLayout->addStretch(10);
    bottomBarLayout->addWidget(apiUsageInfoButton);
    bottomBarLayout->addStretch(1);
    bottomBarLayout->addWidget(closeButton);
    bottomBarLayout->addStretch(1);
    bottomBarLayout->addWidget(resetToDefaultsButton);
    bottomBarLayout->addStretch(10);

    layout->addLayout(bottomBarLayout);
    layout->addStretch(1);

    connect(apiUsageInfoButton, &QPushButton::clicked, this, &SettingsPage::onApiUsageInfoButtonClicked);
    connect(closeButton, &QPushButton::clicked, this, &SettingsPage::onCloseButtonClicked);
    connect(resetToDefaultsButton, &QPushButton::clicked, this, &SettingsPage::onResetToDefaultsButtonClicked);
}

void SettingsPage::reloadData()
{
    setPageData(user::settings::Get());
}

void SettingsPage::onApiUsageInfoButtonClicked()
{
    api_usage::ShowInfo(this);
}

void SettingsPage::onCloseButtonClicked()
{
    if (handleSave())
    {
        emit closePage();
    }
}

void SettingsPage::onResetToDefaultsButtonClicked()
{
    if (handleDiscardQuestion())
    {
        setPageData(user::settings::Defaults());
    }
}

user::settings::Values SettingsPage::collectPageData()
{
    user::settings::Values data;
    data.apiStreetViewLimit = m_propApiStreetViewLimit->getValue();
    data.apiMapsLimit = m_propApiMapsLimit->getValue();
    return data;
}

void SettingsPage::setPageData(const user::settings::Values& data)
{
    m_propApiStreetViewLimit->setValue(data.apiStreetViewLimit);
    m_propApiMapsLimit->setValue(data.apiMapsLimit);
}

bool SettingsPage::handleSave()
{
    user::settings::Values pageData = collectPageData();
    const user::settings::Values& fileData = user::settings::Get();

    if (pageData == fileData)
        return true;

    const auto choice = QMessageBox::question(
        this,
        "Unsaved changes",
        "Save modifications?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (choice == QMessageBox::Cancel)
        return false;

    if (choice == QMessageBox::Yes)
    {
        user::settings::Set(std::move(pageData));
        user::settings::Save();
    }

    return true;
}

bool SettingsPage::handleDiscardQuestion()
{
    const user::settings::Values pageData = collectPageData();
    const user::settings::Values& fileData = user::settings::Get();

    if (pageData == fileData)
        return true;

    const auto choice = QMessageBox::question(
        this,
        "Unsaved changes",
        "Discard modifications?",
        QMessageBox::Yes | QMessageBox::No);

    return choice == QMessageBox::Yes;
}

}