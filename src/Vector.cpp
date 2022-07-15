#include "Vector.h"

#include <QDebug>

Vector::Vector()
        : Vector(0, 0, 0) {
}

Vector::Vector(double x, double y, double z)
        : x(x), y(y), z(z) {
}

double& Vector::operator()(int i) {
    switch(i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

double Vector::operator()(int i) const {
    switch(i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

Vector Vector::projected(const Matrix& m) const {
    Vector ans;
    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            ans(i) += m(i, k) * (*this)(k);
        }
    }
    return ans;
}
