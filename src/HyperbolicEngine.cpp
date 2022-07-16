#include "HyperbolicEngine.h"

#include <QDebug>
#include <math.h>
#include <QRandomGenerator>

const double speed = 0.005;

HyperbolicEngine::HyperbolicEngine() {
    QRandomGenerator rnd;
    for (int i = 0; i < 300; ++i) {
        auto r = rnd.generateDouble();
        auto a = rnd.generateDouble() * 2 * M_PI;

        tail.push_back(r * Vector(cos(a), sin(a), 0));
    }
}

void HyperbolicEngine::move(double horDir, double vertDir) {
    auto nOffset = offset - Vector(horDir, vertDir, 0) * speed;
    if (nOffset.len() < 1) {
        offset = nOffset;
    }
}

Vector applyOffset(const Vector& pt, const Vector& offset) {
    const auto& x = offset;
    auto v = pt; // XXX
    v.z = 0;
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
