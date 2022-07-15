#include "Widget.h"

#include <QTimer>

using namespace std;

Widget::Widget(QWidget* parent) 
        : QWidget(parent) {
    engine = new SphereEngine;

    auto* tailTimer = new QTimer(this);
    connect(tailTimer, &QTimer::timeout,
            this, &Widget::tailTimeout);
    tailTimer->start(10);

    auto* moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout,
            this, &Widget::moveTimeout);
    moveTimer->start(10);
}

Widget::~Widget() {
    delete engine;
}

void Widget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    engine->draw(&qp, size());
}

void Widget::keyPressEvent(QKeyEvent* e) {
    switch(e->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            vertDir -= 1;
            break;

        case Qt::Key_S:
        case Qt::Key_Down:
            vertDir += 1;
            break;

        case Qt::Key_D:
        case Qt::Key_Right:
            horDir -= 1;
            break;

        case Qt::Key_A:
        case Qt::Key_Left:
            horDir += 1;
            break;
    }

    update();
}

void Widget::keyReleaseEvent(QKeyEvent* e) {
    switch(e->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            vertDir += 1;
            break;

        case Qt::Key_S:
        case Qt::Key_Down:
            vertDir -= 1;
            break;

        case Qt::Key_D:
        case Qt::Key_Right:
            horDir += 1;
            break;

        case Qt::Key_A:
        case Qt::Key_Left:
            horDir -= 1;
            break;
    }

    update();
}

void Widget::moveTimeout() {
    engine->move(horDir, vertDir);
    update();
}

void Widget::tailTimeout() {
    engine->updateTail(vertDir == 0 && horDir == 0);
}
