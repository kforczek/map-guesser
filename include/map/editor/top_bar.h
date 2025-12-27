#pragma once
#include <qboxlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

namespace map::editor
{

class TopBar final : public QWidget
{
    Q_OBJECT
public:
    explicit TopBar(QWidget* parent);

    void setSaveEnabled(bool enabled);
    void setMapDisplayPath(const QString& path);

signals:
    void loadButtonClicked();
    void saveButtonClicked();
    void saveAsButtonClicked();

private /*fields*/:
    QHBoxLayout m_layout;

    QLabel m_infoLabel;
    QPushButton m_loadButton;
    QPushButton m_saveButton;
    QPushButton m_saveAsButton;

private /*methods*/:
    void setupInfoLabel();
    void setupLoadButton();
    void setupSaveButton();
    void setupSaveAsButton();
};

}
