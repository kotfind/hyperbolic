#include "Engine.h"

#include <QDebug>

using namespace std;

Engine::Engine()
    : center(0, 0, 1) {
    tail.push_back(center);
}

void Engine::updateTail(bool isStatic) {
    if (!isStatic) {
        tail.push_back(mapToLocal(center));
    }
    while (tail.size() > tailLength) {
        tail.pop_front();
    }
}

std::list<Vector> Engine::getTail() {
    auto ans = tail;
    for (auto& pt : ans) {
        pt = mapToGlobal(pt);
    }
    return ans;
}
