#include "RenderSystem.h"
#include "../components/Components.h"
#include "../managers/ResourceManager.h"

RenderSystem::RenderSystem(SDL_Renderer *renderer, ResourceManager *rm)
    : renderer(renderer), resourceManager(rm) {}

void RenderSystem::update(ECS &ecs, GameManager &gameManager, float fps)
{
    // Clear screen with sky blue background (135, 206, 235)
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
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
        auto *entityType = ecs.getComponent<EntityType>(entityID);

        if (sprite)
        {
            // Load texture if not already loaded
            if (!sprite->texture && entityType)
            {
                std::string texturePath;

                // Determine texture path based on entity type
                if (entityType->type == "player")
                {
                    // For player entities, check movement direction to select appropriate sprite
                    auto *movementDir = ecs.getComponent<MovementDirection>(entityID);
                    if (movementDir && movementDir->direction == MovementDirection::VERTICAL)
                    {
                        texturePath = "art/playerGrey_up1.png";
                    }
                    else
                    {
                        texturePath = "art/playerGrey_walk1.png";
                    }
                }
                else if (entityType->type == "flying")
                {
                    texturePath = "art/enemyFlyingAlt_1.png";
                }
                else if (entityType->type == "swimming")
                {
                    texturePath = "art/enemySwimming_1.png";
                }
                else if (entityType->type == "walking")
                {
                    texturePath = "art/enemyWalking_1.png";
                }

                if (!texturePath.empty())
                {
                    sprite->texture = resourceManager->loadTexture(texturePath);
                }
            }

            if (sprite->texture)
            {
                // Get the actual texture dimensions
                int textureWidth, textureHeight;
                SDL_QueryTexture(sprite->texture, nullptr, nullptr, &textureWidth, &textureHeight);

                SDL_Rect destRect = {
                    static_cast<int>(transform.x - sprite->width / 2),
                    static_cast<int>(transform.y - sprite->height / 2),
                    sprite->width,
                    sprite->height};

                // Source rectangle should use the actual texture dimensions
                int frameWidth = textureWidth;
                if (sprite->animated && sprite->frameCount > 1)
                {
                    frameWidth = textureWidth / sprite->frameCount;
                }

                SDL_Rect srcRect = {0, 0, frameWidth, textureHeight};

                // Handle animation frames
                if (animation && sprite->animated && sprite->frameCount > 1)
                {
                    srcRect.x = (animation->currentFrame % sprite->frameCount) * frameWidth;
                }

                SDL_RenderCopy(renderer, sprite->texture, &srcRect, &destRect);
            }
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
