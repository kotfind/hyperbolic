#pragma once

#include "Canvas.h"

#include <QWidget>
#include <QKeyEvent>

class MainWindow : public QWidget {
    public:
        MainWindow(QWidget* parent = nullptr);

    private:
        Canvas* canvas;
};
