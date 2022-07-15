#pragma once

#include "Engine.h"

class PlaneEngine : public Engine {
    public:
        PlaneEngine();

        void move(int horDir, int vertDir);
        std::list<Vector> getTail() const;
        Vector getRealCenterPoint() const;

    private:
        Vector offset;
};
