#pragma once
#include <QFrame>

class QVBoxLayout;

namespace ui::pages
{

class StartPage final : public QFrame
{
    Q_OBJECT
public:
    explicit StartPage(QWidget* parent);

signals:
    void singlePlayerRequested();
    void mapEditorRequested();
    void settingsRequested();

private /*methods*/:
    void addGameplayButtons(QVBoxLayout& layout);
    void addExtraButtons(QVBoxLayout& layout);
};

}
