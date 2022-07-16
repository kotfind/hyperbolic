#pragma once

#include "Canvas.h"

#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>

class MainWindow : public QMainWindow {
    public:
        MainWindow(QWidget* parent = nullptr);

    private:
        Canvas* canvas;
};
