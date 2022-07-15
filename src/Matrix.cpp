#include "Matrix.h"

#include <math.h>

using namespace std;

Matrix::Matrix()
    : a(3, vector<double>(3, 0)){
}

Matrix::Matrix(const vector<vector<double>>& a) 
    : a(a) {
}

void Matrix::toIdentity() {
    a = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
}

void Matrix::xrot(double a, bool reversed) {
    if (reversed) {
        a = -a;
    }
    auto s = sin(a);
    auto c = cos(a);
    Matrix m({
        { 1,  0, 0},
        { 0,  c, s},
        { 0, -s, c},
    });
    if (reversed) {
        *this = *this * m;
    } else {
        *this = m * *this;
    }
}

void Matrix::yrot(double a, bool reversed) {
    if (reversed) {
        a = -a;
    }
    auto s = sin(a);
    auto c = cos(a);
    Matrix m({
        { c,  0, s},
        { 0,  1, 0},
        {-s,  0, c},
    });
    if (reversed) {
        *this = *this * m;
    } else {
        *this = m * *this;
    }
}

double& Matrix::operator()(int i, int j) {
    return a[i][j];
}

double Matrix::operator()(int i, int j) const {
    return a[i][j];
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    Matrix ans;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                ans(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return ans;
}
