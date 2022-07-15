#pragma once

#include "Vector.h"

#include <QPaintEvent>
#include <QPainter>
#include <list>

class Engine {
    public:
        virtual void move(int horDir, int vertDir) = 0;
        virtual std::list<Vector> getTail() const = 0;
        virtual Vector getRealCenterPoint() const = 0;

        void updateTail(bool isStatic);

    protected:
        const int maxTail = 150;
        std::list<Vector> tail;
};
