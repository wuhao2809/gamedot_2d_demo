#include "InputSystem.h"
#include "../components/Components.h"

InputSystem::InputSystem()
{
    keyboardState = SDL_GetKeyboardState(nullptr);
}

void InputSystem::update(ECS &ecs, GameManager &gameManager, float deltaTime)
{
    // Handle game state inputs
    if (keyboardState[SDL_SCANCODE_SPACE])
    {
        if (gameManager.currentState == GameManager::MENU ||
            gameManager.currentState == GameManager::GAME_OVER)
        {
            gameManager.startGame();
        }
    }

    // Handle player movement (only during gameplay)
    if (gameManager.currentState == GameManager::PLAYING)
    {
        auto &playerEntities = ecs.getComponents<PlayerTag>();

        for (auto &[entityID, playerTag] : playerEntities)
        {
            auto *velocity = ecs.getComponent<Velocity>(entityID);
            if (!velocity)
                continue;

            // Reset velocity
            velocity->x = 0;
            velocity->y = 0;

            // Update velocity based on input
            if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
            {
                velocity->x = -1.0f;
            }
            if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
            {
                velocity->x = 1.0f;
            }
            if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W])
            {
                velocity->y = -1.0f;
            }
            if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S])
            {
                velocity->y = 1.0f;
            }

            // Normalize diagonal movement
            if (velocity->x != 0 && velocity->y != 0)
            {
                velocity->x *= 0.707f; // 1/sqrt(2)
                velocity->y *= 0.707f;
            }
        }
    }
}
