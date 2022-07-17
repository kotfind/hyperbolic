#include "LeapMotion.h"

#include <QDebug>
#include <math.h>

LeapMotion::LeapMotion()
        : listener(horDir, vertDir, validDirs) {
    addListener(listener);
}

// Listener

LeapMotion::Listener::Listener(double& horDir, double& vertDir, bool& validDirs)
        : horDir(horDir), vertDir(vertDir), validDirs(validDirs) {
}

double f(double x) {
    int sgn = (x > 0) - (x < 0);
    x = abs(x);
    return sgn * std::max(0., x - 20) / 50;
}

void LeapMotion::Listener::onFrame(const Leap::Controller& controller) {
    const auto& hands = controller.frame().hands();
    if (!(validDirs = !hands.isEmpty())) return;

    const auto& pos = hands[0].palmPosition();

    horDir = f(pos.x);
    vertDir = -f(pos.z);
}
