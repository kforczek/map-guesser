#pragma once
#include <QWebEngineView>
#include "geo/point.h"

class QWidget;

namespace ui::api_usage
{
class Counter;
}

namespace ui::google
{

class StreetViewBridge;

class StreetView final : public QWebEngineView
{
public:
    explicit StreetView(QWidget* parent, api_usage::Counter& apiUsageCounter);

    const geo::Point& getLocation() const;
    void setLocation(const geo::Point& location);
    void returnToStart();

private:
    StreetViewBridge* m_bridge = nullptr;
    geo::Point m_location;

    bool tryIncreaseApiCounter(api_usage::Counter& counter);

    void initViewSettings() const;
    void initBridge();
    void initHtmlContent();
};

}
