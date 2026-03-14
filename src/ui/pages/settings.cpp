#include "ui/pages/settings.h"
#include "user/settings.h"

#include <qboxlayout.h>
#include <QMessageBox>
#include <QPushButton>

#include "ui/api_usage/counter.h"
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

SettingsPage::SettingsPage(QWidget* parent, const api_usage::Counter& apiUsageCounter)
    : QFrame(parent)
    , m_apiUsageCounter(&apiUsageCounter)
    , m_propApiStreetViewLimit(new widgets::PositiveNumberPropertyEditor(this, API_STREETVIEW_LIMIT_PROP_NAME, API_USAGE_VALS))
    , m_propApiMapsLimit(new widgets::PositiveNumberPropertyEditor(this, API_MAPS_LIMIT_PROP_NAME, API_USAGE_VALS))
{
    auto* layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addStretch(10);
    layout->addWidget(m_propApiStreetViewLimit);
    layout->addWidget(m_propApiMapsLimit);
    layout->addStretch(10);

    auto* apiUsageInfoButton = new QPushButton("API usage info");
    auto* closeButton = new QPushButton("Close");

    apiUsageInfoButton->setFixedSize(150, 50);
    closeButton->setFixedSize(300, 50);

    auto* bottomBarLayout = new QHBoxLayout;
    bottomBarLayout->addStretch(10);
    bottomBarLayout->addWidget(apiUsageInfoButton);
    bottomBarLayout->addStretch(1);
    bottomBarLayout->addWidget(closeButton);
    bottomBarLayout->addStretch(10);

    layout->addLayout(bottomBarLayout);
    layout->addStretch(1);

    connect(apiUsageInfoButton, &QPushButton::clicked, this, &SettingsPage::onApiUsageInfoButtonClicked);
    connect(closeButton, &QPushButton::clicked, this, &SettingsPage::onCloseButtonClicked);
}

void SettingsPage::reloadData()
{
    const user::settings::Values data = user::settings::Get();
    m_propApiStreetViewLimit->setValue(data.apiStreetViewLimit);
    m_propApiMapsLimit->setValue(data.apiMapsLimit);
}

void SettingsPage::onCloseButtonClicked()
{
    handleSave();
    emit closePage();
}

void SettingsPage::onApiUsageInfoButtonClicked()
{
    api_usage::ShowInfo(this, m_apiUsageCounter->getStats());
}

user::settings::Values SettingsPage::collectPageData()
{
    user::settings::Values data;
    data.apiStreetViewLimit = m_propApiStreetViewLimit->getValue();
    data.apiMapsLimit = m_propApiMapsLimit->getValue();
    return data;
}

void SettingsPage::handleSave()
{
    const user::settings::Values pageData = collectPageData();
    const user::settings::Values fileData = user::settings::Get();

    if (pageData == fileData)
        return;

    const bool save = QMessageBox::question(
        this,
        "Save changes?",
        "Do you want to save changes?",
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;

    if (save)
    {
        user::settings::Set(pageData);
        user::settings::Save();
    }

}

}