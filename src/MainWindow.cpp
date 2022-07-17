#include "MainWindow.h"

#include <QSplitter>
#include <QFormLayout>
#include <QSlider>
#include <QFrame>
#include <QComboBox>

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent) {
    setContentsMargins(10, 10, 10, 10);

    // Spliter
    auto* splitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(splitter);

    // Canvas
    canvas = new Canvas(this);
    canvas->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    splitter->addWidget(canvas);

    // Form
    auto* formFrame = new QFrame(this);
    formFrame->setFrameStyle(QFrame::StyledPanel);
    splitter->addWidget(formFrame);

    auto* form = new QFormLayout;
    formFrame->setLayout(form);


    // Geometry Combobox
    auto* geomCombo = new QComboBox(this);
    geomCombo->addItem(tr("Plane"), Engine::PlaneEngineType);
    geomCombo->addItem(tr("Sphere"), Engine::SphereEngineType);
    geomCombo->addItem(tr("Hyperbolic"), Engine::HyperbolicEngineType);
    connect(geomCombo, &QComboBox::currentTextChanged, [=](const QString& s) {
        canvas->setEngineType(geomCombo->currentData().value<Engine::EngineType>());
    });
    form->addRow(tr("Geometry Engine:"), geomCombo);

    // Tail Length
    auto* tailLength = new QSlider(Qt::Horizontal);
    tailLength->setRange(1, 1000);
    tailLength->setValue(400);
    connect(tailLength, &QSlider::valueChanged,
            canvas, &Canvas::setTailLength);
    form->addRow(tr("Tail Length:"), tailLength);

    splitter->setStretchFactor(0, 5);
    splitter->setStretchFactor(1, 1);
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
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

    canvas->setDirs(horDir, vertDir);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
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

    canvas->setDirs(horDir, vertDir);
}

void MainWindow::focusOutEvent(QFocusEvent* e) {
    Q_UNUSED(e);
    canvas->setDirs(0, 0);
}

void MainWindow::focusInEvent(QFocusEvent* e) {
    Q_UNUSED(e);
    canvas->setDirs(0, 0);
}
