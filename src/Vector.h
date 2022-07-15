#pragma once

#include "Matrix.h"

struct Vector {
    Vector();
    Vector(double x, double y, double z);

    double& operator()(int i);
    double operator()(int i) const;

    Vector projected(const Matrix&) const;

    double x, y, z;
};
