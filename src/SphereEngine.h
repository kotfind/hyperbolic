#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Engine.h"

#include <list>

class SphereEngine : public Engine {
    public:
        SphereEngine();

        void draw(QPainter* paint, const QSize& widgetSize);
        void move(int horDir, int vertDir);
        void updateTail(bool isStatic);

    private:
        const Vector pt;
        Matrix matrix;
        Matrix rMatrix;

        const int maxTail = 150;
        std::list<Vector> tail;
};
