#include "HyperbolicEngine.h"

#include <QDebug>
#include <math.h>

const double speed = 0.005;

HyperbolicEngine::HyperbolicEngine() {
}

void HyperbolicEngine::move(double horDir, double vertDir) {
    auto nOffset = offset - Vector(horDir, vertDir, 0) * speed;
    if (nOffset.len() < 1) {
        offset = nOffset;
    }
}

Vector applyOffset(const Vector& pt, const Vector& offset) {
    auto x = pt; // XXX
    x.z = 0;
    const auto& v = offset;
    return (v * (1 + 2 * v * x + x * x) + x * (1 - v * v)) /
        // --------------------------------------------------
            (1 + 2 * v * x + v * v * x * x);
}

Vector HyperbolicEngine::mapToGlobal(const Vector& pt) const {
    return applyOffset(pt, offset);
}

Vector HyperbolicEngine::mapToLocal(const Vector& pt) const {
    return applyOffset(pt, -offset);
}
