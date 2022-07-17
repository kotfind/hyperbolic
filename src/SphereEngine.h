#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Engine.h"

#include <list>

class SphereEngine : public Engine {
    public:
        SphereEngine();

        void move(double horDir, double vertDir);
        Vector mapToGlobal(const Vector& pt) const;
        Vector mapToLocal(const Vector& pt) const;
        EngineType getType() const { return SphereEngineType; }

        double getBallRadius(const Vector& pt) const;
        QColor getBallColor(const Vector& pt) const;

    private:
        Matrix matrix;
        Matrix rMatrix;
};
