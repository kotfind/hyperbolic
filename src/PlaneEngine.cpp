#include "PlaneEngine.h"

#include <QDebug>

const double speed = 0.01;

PlaneEngine::PlaneEngine() {
}

void PlaneEngine::move(int horDir, int vertDir) {
    auto nOffset = offset + Vector(horDir, vertDir, 0) * speed;
    if (nOffset.len() < 1) {
        offset = nOffset;
    }
}

Vector PlaneEngine::getRealCenterPoint() const {
    return -offset;
}

std::list<Vector> PlaneEngine::getTail() const {
    auto ans = tail;
    for (auto& pt : ans) {
        pt += offset;
    }
    return ans;
}
