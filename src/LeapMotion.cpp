#include "LeapMotion.h"

#include <QDebug>

LeapMotion::LeapMotion()
        : listener(horDir, vertDir, validDirs) {
    addListener(listener);
}

// Listener

LeapMotion::Listener::Listener(double& horDir, double& vertDir, bool& validDirs)
        : horDir(horDir), vertDir(vertDir), validDirs(validDirs) {
}

void LeapMotion::Listener::onFrame(const Leap::Controller& controller) {
    const auto& hands = controller.frame().hands();
    if (!(validDirs = !hands.isEmpty())) return;

    const auto& hand = hands[0];

    horDir = -hand.palmNormal().roll() / M_PI * 2;
    vertDir = -hand.direction().pitch() / M_PI * 5;
}
