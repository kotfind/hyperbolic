#pragma once

#include "Vector.h"
#include "Matrix.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <list>

class Widget : public QWidget {
    public:
        Widget(QWidget* parent = nullptr);

    private:
        void draw(QPainter*);

        QPointF mapToScreen(const Vector&);
        double mapToScreen(double r);

        void paintEvent(QPaintEvent*);
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);

        void moveTimeout();
        void tailTimeout();

        const Vector pt;
        Matrix matrix;
        Matrix rMatrix;

        const int maxTail = 150;
        std::list<Vector> tail;

        int horDir = 0; // -1, 0 or 1
        int vertDir = 0; // -1, 0 or 1
};
