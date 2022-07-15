#include "Engine.h"

#include <QDebug>

void Engine::updateTail(bool isStatic) {
    if (!isStatic) {
        tail.push_back(getRealCenterPoint());
    }
    while (tail.size() > maxTail) {
        tail.pop_front();
    }
}
