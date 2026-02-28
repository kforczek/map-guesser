#pragma once
#include <QWebEngineView>
#include "geo/point.h"

class QWidget;

namespace ui::google
{

class StreetViewBridge;

class StreetView final : public QWebEngineView
{
public:
    explicit StreetView(QWidget* parent = nullptr);

    const geo::Point& getLocation() const;
    void setLocation(const geo::Point& location);
    void returnToStart();

private:
    StreetViewBridge* m_bridge = nullptr;
    geo::Point m_location;

    void initViewSettings() const;
    void initBridge();
    void initHtmlContent();
};

}
