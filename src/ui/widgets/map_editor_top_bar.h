#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSpacerItem>

namespace ui::widgets
{

class MapEditorTopBar final : public QWidget
{
    Q_OBJECT
public:
    explicit MapEditorTopBar(QWidget* parent);

    void setSaveEnabled(bool enabled);
    void setMapDisplayPath(const QString& path);

signals:
    void loadButtonClicked();
    void saveButtonClicked();
    void saveAsButtonClicked();
    void closeButtonClicked();

private /*fields*/:
    QHBoxLayout m_layout;

    QLabel m_infoLabel;
    QPushButton m_loadButton;
    QPushButton m_saveButton;
    QPushButton m_saveAsButton;

    QSpacerItem m_spacer;
    QPushButton m_closeButton;

private /*methods*/:
    void setupInfoLabel();
    void setupLoadButton();
    void setupSaveButton();
    void setupSaveAsButton();
    void setupSpacer();
    void setupCloseButton();
};

}
