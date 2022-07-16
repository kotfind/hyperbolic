#pragma once

#include "Engine.h"

class PlaneEngine : public Engine {
    public:
        PlaneEngine();

        void move(double horDir, double vertDir);
        Vector mapToGlobal(const Vector& pt) const;
        Vector mapToLocal(const Vector& pt) const;
        EngineType getType() const { return PlaneEngineType; }

    private:
        Vector offset;
};
