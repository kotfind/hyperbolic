#pragma once

QPointF mapToScreen(const QSize& widgetSize, const Vector& p) {
    double x = p.x;
    double y = p.y;
    y = -y;
    auto w = widgetSize.width();
    auto h = widgetSize.height();
    auto m = std::min(w, h) / 2;
    x = x * m + w / 2;
    y = y * m + h / 2;
    return {x, y};
}

double mapToScreen(const QSize& widgetSize, double r) {
    auto w = widgetSize.width();
    auto h = widgetSize.height();
    auto m = std::min(w, h) / 2;
    return r * m;
}
