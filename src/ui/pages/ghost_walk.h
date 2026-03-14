#pragma once
#include <QFrame>
#include "geo/point.h"

namespace ui::api_usage
{
class Counter;
}

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
    explicit GhostWalkPage(QWidget* parent, api_usage::Counter& apiUsageCounter);

    void setLocation(const geo::Point& location);

signals:
    void closePage();

private /*fields*/:
    api_usage::Counter* m_apiUsageCounter = nullptr;

    google::StreetView* m_streetView = nullptr;
    geo::Point m_currLocation;

private /*methods*/:
    void ensureInitialized();
};

}
