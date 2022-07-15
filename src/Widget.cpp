#include "Widget.h"

#include <QTimer>
#include <QDebug>

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
    // delete engine; // TODO
}

QPointF Widget::mapToScreen(const Vector& p) {
    double x = p.x;
    double y = p.y;
    y = -y;
    auto w = size().width();
    auto h = size().height();
    auto m = min(w, h) / 2;
    x = x * m + w / 2;
    y = y * m + h / 2;
    return {x, y};
}

double Widget::mapToScreen(double r) {
    auto w = size().width();
    auto h = size().height();
    auto m = min(w, h) / 2;
    return r * m;
}

void Widget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    draw(&qp);
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

void Widget::draw(QPainter* qp) {
    double r;
    // Draw circle
    r = mapToScreen(1);
    qp->drawEllipse(mapToScreen({0, 0, 0}), r, r);

    // Brushes
    QBrush brush = qp->brush();
    brush.setStyle(Qt::SolidPattern);
    QPen pen = qp->pen();
    pen.setWidthF(0.5);
    qp->setPen(pen);

    // Draw tail
    for (const auto& pt : engine->getTail()) {
        auto color = pt.z > 0 ? Qt::red : Qt::green;

        brush.setColor(color);
        qp->setBrush(brush);

        r = (pt.z + 1) * 2 + 1;
        qp->drawEllipse(mapToScreen(pt), r, r);
    }
}

void Widget::moveTimeout() {
    engine->move(horDir, vertDir);
    update();
}

void Widget::tailTimeout() {
    engine->updateTail(vertDir == 0 && horDir == 0);
}
