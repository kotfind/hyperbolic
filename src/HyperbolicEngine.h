#pragma once

#include "Engine.h"

class HyperbolicEngine : public Engine {
    public:
        HyperbolicEngine();

        void move(double horDir, double vertDir);
        Vector mapToGlobal(const Vector& pt) const;
        Vector mapToLocal(const Vector& pt) const;
        EngineType getType() const { return HyperbolicEngineType; }

        double getBallRadius(const Vector& pt) const;
        QColor getBallColor(const Vector& pt) const;

    private:
        Vector offset;
};
