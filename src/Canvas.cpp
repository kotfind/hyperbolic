#include "Canvas.h"

#include <QTimer>
#include <QDebug>

using namespace std;

Canvas::Canvas(QWidget* parent) 
        : QWidget(parent) {
    planeEngine = new PlaneEngine;
    sphereEngine = new SphereEngine;

    engineType = Engine::PlaneEngineType;
    engine = planeEngine;

    auto* tailTimer = new QTimer(this);
    connect(tailTimer, &QTimer::timeout,
            this, &Canvas::tailTimeout);
    tailTimer->start(10);

    auto* moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout,
            this, &Canvas::moveTimeout);
    moveTimer->start(10);
}

Canvas::~Canvas() {
    engine = nullptr;
    delete sphereEngine;
    delete planeEngine;
}

QPointF Canvas::mapToScreen(const Vector& p) {
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

double Canvas::mapToScreen(double r) {
    auto w = size().width();
    auto h = size().height();
    auto m = min(w, h) / 2;
    return r * m;
}

void Canvas::keyPressEvent(QKeyEvent* e) {
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

void Canvas::keyReleaseEvent(QKeyEvent* e) {
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

void Canvas::focusOutEvent(QFocusEvent* e) {
    Q_UNUSED(e);
    horDir = 0;
    vertDir = 0;
}

void Canvas::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    draw(&qp);
}

void Canvas::draw(QPainter* qp) {
    double r;
    // Draw circle
    r = mapToScreen(1);
    qp->drawEllipse(mapToScreen(engine->mapToGlobal({0, 0, 0})), r, r);

    // Brushes
    QBrush brush = qp->brush();
    brush.setStyle(Qt::SolidPattern);
    qp->setPen(Qt::NoPen);

    // Draw tail
    for (const auto& pt : engine->getTail()) {
        brush.setColor(QColor(255, 0, 0, 100 + 155 * (pt.z + 1) / 2));
        qp->setBrush(brush);

        r = (pt.z + 1) * 2 + 1;
        qp->drawEllipse(mapToScreen(pt), r, r);
    }
}

void Canvas::moveTimeout() {
    engine->move(max(-1, min(1, horDir)), max(-1, min(1, vertDir)));
    update();
}

void Canvas::tailTimeout() {
    engine->updateTail();
}

void Canvas::setTailLength(int l) {
    engine->setTailLength(l);
    update();
}

void Canvas::setEngineType(Engine::EngineType type) {
    engineType = type;
    switch(type) {
        case Engine::PlaneEngineType:
            engine = planeEngine;
            break;

        case Engine::SphereEngineType:
            engine = sphereEngine;
            break;
    }
}
