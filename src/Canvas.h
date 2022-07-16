#include "Engine.h"
#include "SphereEngine.h"
#include "PlaneEngine.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>

class Canvas : public QWidget {
    public:
        Canvas(QWidget* parent = nullptr);
        ~Canvas();

    private:
        Engine* engine;

        QPointF mapToScreen(const Vector& p);
        double mapToScreen(double r);

        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);
        void paintEvent(QPaintEvent*);

        void draw(QPainter* qp);

        void moveTimeout();
        void tailTimeout();

        int horDir = 0; // -1, 0 or 1
        int vertDir = 0; // -1, 0 or 1
};