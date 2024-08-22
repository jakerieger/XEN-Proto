#include "Core/Game.h"

class Pong final : public IGame {
public:
    Pong() : IGame("Pong <OpenGL 4.6>") {}

    void Initialize() override {
        const auto gameScene = std::make_shared<Scene>();
        this->LoadScene(gameScene);
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
