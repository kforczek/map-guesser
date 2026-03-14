#pragma once
#include <QFrame>
#include "geo/point.h"

namespace ui::google
{
class StreetView;
}

namespace ui::pages
{

class GhostWalkPage final : public QFrame
{
    Q_OBJECT
public:
    explicit GhostWalkPage(QWidget* parent);

    void setLocation(const geo::Point& location);

signals:
    void closePage();

private /*fields*/:
    google::StreetView* m_streetView = nullptr;
    geo::Point m_currLocation;

private /*methods*/:
    void ensureInitialized();
};

}
