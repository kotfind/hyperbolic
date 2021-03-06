#include "Canvas.h"

#include <QTimer>
#include <QDebug>

using namespace std;

Canvas::Canvas(QWidget* parent) 
        : QWidget(parent) {
    planeEngine = new PlaneEngine;
    sphereEngine = new SphereEngine;
    hyperbolicEngine = new HyperbolicEngine;

    leapmotion = new LeapMotion;

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
    delete hyperbolicEngine;
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

void Canvas::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    draw(&qp);
}

void Canvas::draw(QPainter* qp) {
    double r;
    // Draw circle
    r = mapToScreen(1);
    qp->drawEllipse(
        mapToScreen(engineType == Engine::PlaneEngineType
            ? engine->mapToGlobal({0, 0, 1})
            : Vector(0, 0, 0)),
        r, r);

    // Brushes
    QBrush brush = qp->brush();
    brush.setStyle(Qt::SolidPattern);
    qp->setPen(Qt::NoPen);

    // Draw tail
    for (const auto& pt : engine->getTail()) {
        brush.setColor(engine->getBallColor(pt));
        qp->setBrush(brush);

        r = engine->getBallRadius(pt);
        qp->drawEllipse(mapToScreen(pt), r, r);
    }
}

void Canvas::moveTimeout() {
    if (leapmotion->validDirs) {
        engine->move(
            max(-1., min(1., leapmotion->horDir)),
            max(-1., min(1., leapmotion->vertDir)));
    }

    engine->move(
        max(-1., min(1., horDir)),
        max(-1., min(1., vertDir)));

    update();
}

void Canvas::tailTimeout() {
    engine->updateTail();
}

void Canvas::setTailLength(int l) {
    planeEngine->setTailLength(l);
    sphereEngine->setTailLength(l);
    hyperbolicEngine->setTailLength(l);
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

        case Engine::HyperbolicEngineType:
            engine = hyperbolicEngine;
            break;
    }
}

void Canvas::setDirs(double hor, double vert) {
    horDir = hor;
    vertDir = vert;
}
