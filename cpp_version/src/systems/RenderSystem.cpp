#include "RenderSystem.h"
#include "../components/Components.h"
#include "../managers/ResourceManager.h"

RenderSystem::RenderSystem(SDL_Renderer *renderer, ResourceManager *rm)
    : renderer(renderer), resourceManager(rm) {}

void RenderSystem::update(ECS &ecs, GameManager &gameManager, float fps)
{
    // Clear screen with black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render game sprites
    renderSprites(ecs);

    // Render UI
    renderUI(ecs, gameManager, fps);

    // Present frame
    SDL_RenderPresent(renderer);
}

void RenderSystem::renderSprites(ECS &ecs)
{
    auto &transforms = ecs.getComponents<Transform>();

    for (auto &[entityID, transform] : transforms)
    {
        auto *sprite = ecs.getComponent<Sprite>(entityID);
        auto *animation = ecs.getComponent<Animation>(entityID);

        if (sprite && sprite->texture)
        {
            SDL_Rect destRect = {
                static_cast<int>(transform.x - sprite->width / 2),
                static_cast<int>(transform.y - sprite->height / 2),
                sprite->width,
                sprite->height};

            SDL_Rect srcRect = {0, 0, sprite->width, sprite->height};

            // Handle animation frames
            if (animation && sprite->animated && sprite->frameCount > 1)
            {
                srcRect.x = (animation->currentFrame % sprite->frameCount) * sprite->width;
            }

            SDL_RenderCopy(renderer, sprite->texture, &srcRect, &destRect);
        }
    }
}

void RenderSystem::renderUI(ECS &ecs, GameManager &gameManager, float fps)
{
    auto &uiPositions = ecs.getComponents<UIPosition>();

    for (auto &[entityID, uiPos] : uiPositions)
    {
        auto *uiText = ecs.getComponent<UIText>(entityID);
        if (!uiText || !uiText->visible)
            continue;

        // Load font if not already loaded
        TTF_Font *font = resourceManager->getFont(uiText->fontPath, uiText->fontSize);
        if (!font)
        {
            font = resourceManager->loadFont(uiText->fontPath, uiText->fontSize);
        }

        if (font)
        {
            // Create text texture
            SDL_Texture *textTexture = resourceManager->createTextTexture(
                uiText->content, font, uiText->color);

            if (textTexture)
            {
                int textWidth, textHeight;
                SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

                SDL_Rect destRect = {
                    static_cast<int>(uiPos.x),
                    static_cast<int>(uiPos.y),
                    textWidth,
                    textHeight};

                SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);
                SDL_DestroyTexture(textTexture);
            }
        }
    }
}
