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
