#pragma once

#include "Vector.h"

#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <list>

class Engine {
    public:
        enum EngineType {
            PlaneEngineType,
            SphereEngineType,
            HyperbolicEngineType,
        };

        Engine();

        virtual void move(double horDir, double vertDir) = 0;
        virtual Vector mapToGlobal(const Vector& pt) const = 0;
        virtual Vector mapToLocal(const Vector& pt) const = 0;
        virtual EngineType getType() const = 0;

        virtual double getBallRadius(const Vector& pt) const = 0;
        virtual QColor getBallColor(const Vector& pt) const = 0;

        void updateTail();
        std::list<Vector> getTail();

        void setTailLength(int l) { tailLength = l; }

        const Vector center;

    protected:
        int tailLength = 150;
        std::list<Vector> tail;
};

Q_DECLARE_METATYPE(Engine::EngineType)

