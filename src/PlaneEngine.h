#pragma once

#include "Engine.h"

class PlaneEngine : public Engine {
    public:
        PlaneEngine();

        void move(int horDir, int vertDir);
        Vector mapToGlobal(const Vector& pt) const;
        Vector mapToLocal(const Vector& pt) const;

    private:
        Vector offset;
};
