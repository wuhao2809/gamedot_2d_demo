#pragma once
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class ResourceManager; // Forward declaration

class RenderSystem : public System
{
private:
    SDL_Renderer *renderer;
    ResourceManager *resourceManager;

public:
    RenderSystem(SDL_Renderer *renderer, ResourceManager *rm);
    void update(ECS &ecs, GameManager &gameManager, float fps);

private:
    void renderSprites(ECS &ecs);
    void renderUI(ECS &ecs, GameManager &gameManager, float fps);
};
