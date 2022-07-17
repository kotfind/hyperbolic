#include "PlaneEngine.h"

#include <QDebug>

const double speed = 0.01;

PlaneEngine::PlaneEngine() {
}

void PlaneEngine::move(double horDir, double vertDir) {
    auto nOffset = offset + Vector(horDir, vertDir, 0) * speed;
    if (nOffset.len() < 1) {
        offset = nOffset;
    }
}

Vector PlaneEngine::mapToGlobal(const Vector& pt) const {
    return pt - offset;
}

Vector PlaneEngine::mapToLocal(const Vector& pt) const {
    return pt + offset;
}

double PlaneEngine::getBallRadius(const Vector& pt) const {
    return 3;
}

QColor PlaneEngine::getBallColor(const Vector& pt) const {
    return QColor(0, 255, 0);
}
