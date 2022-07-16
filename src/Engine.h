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

        void setTailLength(int l) { tailLength = l; }

        const Vector center;

    protected:
        int tailLength = 150;
        std::list<Vector> tail;
};
