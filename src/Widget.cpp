#include "Widget.h"

#include <QDebug>
#include <QPainter>
#include <QTimer>

using namespace std;

const double alpha = 0.01;

Widget::Widget(QWidget* parent) 
        : QWidget(parent), pt(0, 0, 1) {
    matrix.toIdentity();
    rMatrix.toIdentity();

    auto* tailTimer = new QTimer(this);
    connect(tailTimer, &QTimer::timeout,
            this, &Widget::tailTimeout);
    tailTimer->start(10);

    auto* moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout,
            this, &Widget::moveTimeout);
    moveTimer->start(10);
}

void Widget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    draw(&qp);
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
    for (const auto& pt : tail) {
        const auto npt = pt.projected(matrix);

        auto color = npt.z > 0 ? Qt::red : Qt::green;

        brush.setColor(color);

        qp->setBrush(brush);

        r = (npt.z + 1) * 2 + 1;
        qp->drawEllipse(mapToScreen(npt), r, r);
    }

    // Draw point
    auto color = pt.z > 0 ? Qt::black : Qt::gray;
    brush.setColor(color);

    qp->setBrush(brush);

    r = (pt.z + 1) * 2 + 1;
    qp->drawEllipse(mapToScreen(pt), r, r);
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
    matrix.xrot(alpha * vertDir);
    matrix.yrot(alpha * horDir);

    rMatrix.xrot(alpha * vertDir, true);
    rMatrix.yrot(alpha * horDir, true);

    update();
}

void Widget::tailTimeout() {
    if (vertDir != 0 || horDir != 0) {
        tail.push_back(pt.projected(rMatrix));
    }
    while (tail.size() > maxTail) {
        tail.pop_front();
    }
}
