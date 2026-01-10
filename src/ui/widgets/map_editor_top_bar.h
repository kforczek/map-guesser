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
    QLabel* m_infoLabel = nullptr;
    QPushButton* m_loadButton = nullptr;
    QPushButton* m_saveButton = nullptr;
    QPushButton* m_saveAsButton = nullptr;

private /*methods*/:
    void setupInfoLabel();
    void setupLoadButton();
    void setupSaveButton();
    void setupSaveAsButton();
    void setupSpacer();
    void setupCloseButton();
};

}
