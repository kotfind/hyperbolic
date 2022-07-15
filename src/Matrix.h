#pragma once

#include <vector>

struct Matrix {
    Matrix();
    Matrix(const std::vector<std::vector<double>>&);

    void toIdentity();

    void xrot(double a, bool reversed=false);
    void yrot(double a, bool reversed=false);

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    private:
        std::vector<std::vector<double>> a;
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs);
