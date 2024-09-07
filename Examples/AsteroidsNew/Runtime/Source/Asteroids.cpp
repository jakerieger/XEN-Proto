// Author: Jake Rieger
// Created: 9/5/2024.
//

#include "Asteroids.h"
#include "Player.h"
#include "Bullet.h"
#include "Shared/Types.h"

void Asteroids::Create() {
    const auto player = std::make_shared<Player>("Player");
    mInputManager->RegisterListener(player);

    const auto gameScene = CreateScene("Game");
    gameScene->AddGameObject(player);
    gameScene->SetCamera(OrthoCamera::CreateDefault());
    LoadScene("Game");
}