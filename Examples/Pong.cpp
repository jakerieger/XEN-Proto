#include "Player.h"
#include "Core/Game.h"

class Pong final : public IGame {
public:
    Pong() : IGame("Pong <OpenGL 4.6>") {}

    void Initialize() override {
        auto gameScene    = std::make_shared<Scene>();
        const auto player = std::make_shared<Player>();
        gameScene->AddGameObject(player);

        this->AddScene("game", gameScene);
        this->LoadScene("game");
    }

    void Shutdown() override {
        IGame::Shutdown();  // MAKE SURE TO CALL THIS AT THE END
    }

private:
};

int main() {
    Pong game;
    game.Run();

    return 0;
}
