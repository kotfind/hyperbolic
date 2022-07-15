#include "SphereEngine.h"
#include "mapToScreen.h"

#include <QPainter>

const double alpha = 0.01;

SphereEngine::SphereEngine()
        : pt(0, 0, 1) {
    matrix.toIdentity();
    rMatrix.toIdentity();
}

void SphereEngine::draw(QPainter* qp, const QSize& widgetSize) {
    double r;
    // Draw circle
    r = mapToScreen(widgetSize, 1);
    qp->drawEllipse(mapToScreen(widgetSize, {0, 0, 0}), r, r);

    // Brushes
    QBrush brush = qp->brush();
    brush.setStyle(Qt::SolidPattern);
    QPen pen = qp->pen();
    pen.setWidthF(0.5);
    qp->setPen(pen);

    // Draw tail
    for (const auto& pt : tail) {
        const auto npt = pt.projected(matrix);

        auto color = npt.z > 0 ? Qt::red : Qt::green;

        brush.setColor(color);

        qp->setBrush(brush);

        r = (npt.z + 1) * 2 + 1;
        qp->drawEllipse(mapToScreen(widgetSize, npt), r, r);
    }

    // Draw point
    auto color = pt.z > 0 ? Qt::black : Qt::gray;
    brush.setColor(color);

    qp->setBrush(brush);

    r = (pt.z + 1) * 2 + 1;
    qp->drawEllipse(mapToScreen(widgetSize, pt), r, r);
}

void SphereEngine::move(int horDir, int vertDir) {
    matrix.xrot(alpha * vertDir);
    matrix.yrot(alpha * horDir);

    rMatrix.xrot(alpha * vertDir, true);
    rMatrix.yrot(alpha * horDir, true);
}

void SphereEngine::updateTail(bool isStatic) {
    if (!isStatic) {
        tail.push_back(pt.projected(rMatrix));
    }
    while (tail.size() > maxTail) {
        tail.pop_front();
    }
}
