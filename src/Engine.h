#pragma once

#include <QPaintEvent>
#include <QPainter>

class Engine {
    public:
        virtual void draw(QPainter* paint, const QSize& widgetSize) = 0;
        virtual void move(int horDir, int vertDir) = 0;
        virtual void updateTail(bool isStatic) = 0;
};
