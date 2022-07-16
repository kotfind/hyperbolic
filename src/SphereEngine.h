#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Engine.h"

#include <list>

class SphereEngine : public Engine {
    public:
        SphereEngine();

        void move(int horDir, int vertDir);
        Vector mapToGlobal(const Vector& pt) const;
        Vector mapToLocal(const Vector& pt) const;
        EngineType getType() const { return SphereEngineType; }

    private:
        Matrix matrix;
        Matrix rMatrix;
};
