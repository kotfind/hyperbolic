#include "Engine.h"

#include <QDebug>

using namespace std;

Engine::Engine()
    : center(0, 0, 1) {
    tail.push_back(center);
}

void Engine::updateTail() {
    auto pt = mapToLocal(center);
    if (tail.empty() || pt != tail.back()) {
        tail.push_back(pt);
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
