#include "Core/Game.h"

// Game Object classes
#include "Ball.h"
#include "Opponent.h"
#include "Player.h"

#ifndef NDEBUG
static const auto kGameName = "Pong <Debug>";
#else
static const auto kGameName = "Pong";
#endif

class Pong final : public IGame {
public:
    /// Do not initialize any runtime components in the game constructor.
    /// That should be done in `IGame::Initialize()`. Otherwise, you'll create
    /// resources before the classes that own them have been instantiated.
    Pong() : IGame(kGameName) {}

    void Initialize() override {
        // If you have a png file, you can set it as the window icon.
        // The executable icon is set via system-specific resource files,
        // not at runtime.
        SetWindowIcon("Res/icon.png");

        // Create our scenes, just a game scene in this case
        const auto gameScene = std::make_shared<Scene>();

        // Create the game objects that will occupy our scene
        const auto player   = std::make_shared<Player>();
        const auto opponent = std::make_shared<Opponent>();
        const auto ball     = std::make_shared<Ball>();

        // Attach everything to our scene
        gameScene->AddGameObject(player);
        gameScene->AddGameObject(opponent);
        gameScene->AddGameObject(ball);
        // Make sure to set our main camera too, otherwise nothing will
        // display on screen
        gameScene->SetCamera(OrthoCamera::CreateDefault());

        // Register the player class as an input listener so it can receive
        // input events
        mInputManager->RegisterListener(player);

        // Add our scene to our game
        AddScene("game", gameScene);

        // Load our scene
        LoadScene("game");
    }

    void Shutdown() override {
        // TODO: Clean up any resources owned by this class here

        // Make sure to call Shutdown on the parent too or internal engine resources will not be
        // cleaned up properly
        IGame::Shutdown();
    }
};

int main() {
    Pong game;
    game.Run();

    return 0;
}
