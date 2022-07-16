#pragma once

#include "Vector.h"

#include <QPaintEvent>
#include <QPainter>
#include <list>

class Engine {
    public:
        Engine();

        virtual void move(int horDir, int vertDir) = 0;
        virtual Vector mapToGlobal(const Vector& pt) const = 0;
        virtual Vector mapToLocal(const Vector& pt) const = 0;

        void updateTail(bool isStatic);
        std::list<Vector> getTail();

        const Vector center;

    protected:
        const int maxTail = 150;
        std::list<Vector> tail;
};
