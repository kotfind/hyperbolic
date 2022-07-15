#include "SphereEngine.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>

class Widget : public QWidget {
    public:
        Widget(QWidget* parent = nullptr);
        ~Widget();

    private:
        SphereEngine* engine;

        void paintEvent(QPaintEvent*);
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);

        void moveTimeout();
        void tailTimeout();

        int horDir = 0; // -1, 0 or 1
        int vertDir = 0; // -1, 0 or 1
};
