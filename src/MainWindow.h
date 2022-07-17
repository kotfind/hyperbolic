#pragma once

#include "Canvas.h"

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>

class MainWindow : public QMainWindow {
    public:
        MainWindow(QWidget* parent = nullptr);

    private:
        void keyPressEvent(QKeyEvent*);
        void keyReleaseEvent(QKeyEvent*);
        void focusOutEvent(QFocusEvent*);
        void focusInEvent(QFocusEvent*);

        double horDir = 0;
        double vertDir = 0;

        Canvas* canvas;
};
