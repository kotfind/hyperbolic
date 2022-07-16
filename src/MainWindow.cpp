#include "MainWindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* parent)
        : QWidget(parent) {
    auto hbox = new QHBoxLayout;
    setLayout(hbox);

    canvas = new Canvas(this);
    canvas->setFocus();
    hbox->addWidget(canvas, 1);
}
