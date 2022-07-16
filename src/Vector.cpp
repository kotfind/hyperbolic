#include "Vector.h"

#include <QDebug>
#include <math.h>

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

double Vector::len() const {
    double sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += (*this)(i) * (*this)(i);
    }
    return sqrt(sum);
}

Vector operator-(const Vector& v) {
    auto ans = v;
    for (int i = 0; i < 3; ++i) {
        ans(i) = -ans(i);
    }
    return ans;
}

Vector& operator+=(Vector& lhs, const Vector& rhs) {
    for (int i = 0; i < 3; ++i) {
        lhs(i) += rhs(i);
    }
    return lhs;
}

Vector& operator-=(Vector& lhs, const Vector& rhs) {
    for (int i = 0; i < 3; ++i) {
        lhs(i) -= rhs(i);
    }
    return lhs;
}

Vector& operator*=(Vector& lhs, double rhs) {
    for (int i = 0; i < 3; ++i) {
        lhs(i) *= rhs;
    }
    return lhs;
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
    auto ans = lhs;
    ans += rhs;
    return ans;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
    auto ans = lhs;
    ans -= rhs;
    return ans;
}

Vector operator*(const Vector& lhs, double rhs) {
    auto ans = lhs;
    ans *= rhs;
    return ans;
}

Vector operator*(double lhs, const Vector& rhs) {
    return rhs * lhs;
}

bool operator==(const Vector& lhs, const Vector& rhs) {
    for (int i = 0; i < 3; ++i) {
        if (lhs(i) != rhs(i)) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Vector& lhs, const Vector& rhs) {
    return !(lhs == rhs);
}
