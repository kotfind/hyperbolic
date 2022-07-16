#include "SphereEngine.h"

#include <QDebug>

using namespace std;

const double alpha = 0.01;

SphereEngine::SphereEngine() {
    matrix.toIdentity();
    rMatrix.toIdentity();
}

void SphereEngine::move(double horDir, double vertDir) {
    matrix.xrot(-alpha * vertDir);
    matrix.yrot(-alpha * horDir);

    rMatrix.xrot(-alpha * vertDir, true);
    rMatrix.yrot(-alpha * horDir, true);
}

Vector SphereEngine::mapToGlobal(const Vector& pt) const {
    return pt.projected(matrix);
}

Vector SphereEngine::mapToLocal(const Vector& pt) const {
    return pt.projected(rMatrix);
}
