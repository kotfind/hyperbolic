#pragma once

#include "Engine.h"
#include <complex>

class HyperbolicEngine : public Engine {
    public:
        HyperbolicEngine();

        void appendOffset(std::complex<double> b);

        void move(double horDir, double vertDir);

        Vector mapToGlobal(const Vector& pt) const;
        Vector mapToLocal(const Vector& pt) const;
        EngineType getType() const { return HyperbolicEngineType; }

        double getBallRadius(const Vector& pt) const;
        QColor getBallColor(const Vector& pt) const;

    private:
        std::complex<double> offsetA = 1;
        std::complex<double> offsetB = 0;
};
