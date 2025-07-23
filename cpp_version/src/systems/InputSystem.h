#pragma once
#include "System.h"
#include <SDL2/SDL.h>

class InputSystem : public System
{
private:
    const Uint8 *keyboardState;

public:
    InputSystem();
    void update(ECS &ecs, GameManager &gameManager, float deltaTime) override;
};
