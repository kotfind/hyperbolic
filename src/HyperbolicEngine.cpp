#include "HyperbolicEngine.h"

#include <QDebug>
#include <math.h>
#include <complex>

using namespace std;

const double speed = 0.007;

HyperbolicEngine::HyperbolicEngine() {
}

void HyperbolicEngine::appendOffset(complex<double> b1) {
    auto a1 = sqrt(1. + pow(abs(b1), 2));
    auto a2 = offsetA;
    auto b2 = offsetB;
    offsetA = a1 * a2 + conj(b1) * b2;
    offsetB = conj(a1) * b2 + b1 * a2;
}

void HyperbolicEngine::move(double horDir, double vertDir) {
    appendOffset(speed * horDir * -1);
    appendOffset(speed * vertDir * 1i);
}

Vector HyperbolicEngine::mapToGlobal(const Vector& pt) const {
    auto a = offsetA;
    auto b = offsetB;
    complex<double> z = pt.x + pt.y * 1i;
    z = (a * z + conj(b)) / (b * z + conj(a));
    return Vector(z.real(), z.imag(), 0);
}

Vector HyperbolicEngine::mapToLocal(const Vector& pt) const {
    auto a = conj(offsetA);
    auto b = -offsetB;
    complex<double> z = pt.x + pt.y * 1i;
    z = (a * z + conj(b)) / (conj(a) + b * z);
    return Vector(z.real(), z.imag(), 0);
}

double HyperbolicEngine::getBallRadius(const Vector& pt) const {
    return (1 - pt.len()) * 3 + 1;
}

QColor HyperbolicEngine::getBallColor(const Vector& pt) const {
    return {255, 0, 0, 100 + 155 * (1 - pt.len())};
}
