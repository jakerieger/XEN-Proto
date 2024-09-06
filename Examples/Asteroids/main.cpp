// Author: Jake Rieger
// Created: 9/1/2024.
//

#include "XnCore/Game.h"
#include "Player.h"

#ifndef NDEBUGll
static const auto kGameName = "Asteroids <Debug>";
#else
static const auto kGameName = "Asteroids";
#endif

class Asteroids final : public IGame {
public:
    Asteroids() : IGame(kGameName) {}

    void Create() override {
        SetWindowIcon("Res/icon.png");

        const auto player = std::make_shared<Player>("Player");
        mInputManager->RegisterListener(player);

        const auto gameScene = CreateScene("game");
        gameScene->AddGameObject(player);
        gameScene->SetCamera(OrthoCamera::CreateDefault());
        LoadScene("game");
    }

    void Destroy() override {
        IGame::Destroy();
    }
};

int main() {
    Asteroids asteroids;
    asteroids.Run();
    return 0;
}