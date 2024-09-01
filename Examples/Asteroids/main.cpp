// Author: Jake Rieger
// Created: 9/1/2024.
//

#include "XnCore/Game.h"

#ifndef NDEBUG
static const auto kGameName = "Asteroids <Debug>";
#else
static const auto kGameName = "Asteroids";
#endif

class Asteroids final : public IGame {
public:
    Asteroids() : IGame(kGameName) {}

    void Create() override {}

    void Destroy() override {}
};

int main() {
    Asteroids asteroids;
    asteroids.Run();
    return 0;
}