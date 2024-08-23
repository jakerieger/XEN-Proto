#include "Ball.h"
#include "Opponent.h"
#include "Player.h"
#include "Core/Game.h"

#ifndef NDEBUG
static const auto kGameName = "Pong <Debug>";
#else
static const auto kGameName = "Pong";
#endif

class Pong final : public IGame {
public:
    Pong() : IGame(kGameName) {}

    void Initialize() override {
        const auto gameScene = std::make_shared<Scene>();
        const auto player    = std::make_shared<Player>();
        const auto opponent  = std::make_shared<Opponent>();
        const auto ball      = std::make_shared<Ball>();

        gameScene->AddGameObject(player);
        gameScene->AddGameObject(opponent);
        gameScene->AddGameObject(ball);
        gameScene->SetCamera(OrthoCamera::CreateDefault());

        AddScene("game", gameScene);
        LoadScene("game");
    }

    void Shutdown() override {
        // Make sure to call this at the end or internal engine resources will not be cleaned
        // up properly
        IGame::Shutdown();
    }

private:
};

int main() {
    Pong game;
    game.Run();

    return 0;
}
