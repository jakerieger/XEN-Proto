// Author: Jake Rieger
// Created: 9/5/2024.
//

#include "Asteroids.h"
#include "Player.h"
#include "Types.h"

void Asteroids::Create() {
    const auto gameScene = CreateScene("Game");
    gameScene->SetCamera(OrthoCamera::CreateDefault());

    const auto player = CreateGameObject<Player>(gameScene, "Player");
    GetInputManager()->RegisterListener(player);

    LoadScene("Game");
}

void Asteroids::Destroy() {
    IGame::Destroy();
}

IGame* CreateInstance() {
    return new Asteroids;
}

void DestroyInstance(const IGame* instance) {
    delete instance;
}