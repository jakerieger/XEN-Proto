#include "Core/Game.h"

class Pong final : public IGame {
public:
    Pong() : IGame("Pong") {}

    void Initialize() override {}

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
