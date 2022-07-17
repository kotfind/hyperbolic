#pragma once

#include "Engine.h"
#include "SphereEngine.h"
#include "PlaneEngine.h"
#include "HyperbolicEngine.h"
#include "LeapMotion.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QFocusEvent>

class Canvas : public QWidget {
    Q_OBJECT

    public:
        Canvas(QWidget* parent = nullptr);
        ~Canvas();

    private:
        Engine* engine;
        PlaneEngine* planeEngine;
        SphereEngine* sphereEngine;
        HyperbolicEngine* hyperbolicEngine;
        Engine::EngineType engineType;

        LeapMotion* leapmotion;

        QPointF mapToScreen(const Vector& p);
        double mapToScreen(double r);

        void paintEvent(QPaintEvent*);
        void draw(QPainter* qp);

        void moveTimeout();
        void tailTimeout();

        double horDir = 0; // -1, 0 or 1
        double vertDir = 0; // -1, 0 or 1

    public slots:
        void setTailLength(int l);
        void setEngineType(Engine::EngineType type);
        void setDirs(double horDir, double vertDir);
};
