#pragma once

#include "Matrix.h"

struct Vector {
    Vector();
    Vector(double x, double y, double z);

    double& operator()(int i);
    double operator()(int i) const;

    Vector projected(const Matrix&) const;

    double len() const;

    double x, y, z;
};

Vector operator-(const Vector& v);

Vector& operator+=(Vector& lhs, const Vector& rhs);
Vector& operator-=(Vector& lhs, const Vector& rhs);
Vector& operator*=(Vector& lhs, double rhs);
Vector& operator*=(double& lhs, const Vector& rhs);

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(const Vector& lhs, double rhs);
Vector operator*(double lhs, const Vector& rhs);
