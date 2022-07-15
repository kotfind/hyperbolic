#include "SphereEngine.h"

#include <QDebug>

using namespace std;

const double alpha = 0.01;

SphereEngine::SphereEngine() {
    matrix.toIdentity();
    rMatrix.toIdentity();
}

void SphereEngine::move(int horDir, int vertDir) {
    matrix.xrot(alpha * vertDir);
    matrix.yrot(alpha * horDir);

    rMatrix.xrot(alpha * vertDir, true);
    rMatrix.yrot(alpha * horDir, true);
}

Vector SphereEngine::getRealCenterPoint() const {
    return Vector(0, 0, 1).projected(rMatrix);
}

list<Vector> SphereEngine::getTail() const {
    list<Vector> ans = tail;
    for (auto& pt : ans) {
        pt = pt.projected(matrix);
    }
    return ans;
}
