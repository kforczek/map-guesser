#pragma once
#include <QWidget>
#include <vector>

class QVBoxLayout;

namespace ui::widgets
{

class LeaderboardInfoBox final : public QWidget
{
public:
    explicit LeaderboardInfoBox(QWidget* parent = nullptr);

    void reload();

private /*fields*/:
    QVBoxLayout* m_layout;

    class Row;
    std::vector<Row*> m_rows;

private /*methods*/:
    void removeExtraRows();
    void createMissingRows();
    void updateData();
};

}
