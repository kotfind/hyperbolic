#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Engine.h"

#include <list>

class SphereEngine : public Engine {
    public:
        SphereEngine();

        void move(int horDir, int vertDir);
        std::list<Vector> getTail() const;
        Vector getRealCenterPoint() const;

    private:
        Matrix matrix;
        Matrix rMatrix;
};
