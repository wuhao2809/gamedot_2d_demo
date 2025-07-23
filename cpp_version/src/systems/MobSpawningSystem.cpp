#include "MobSpawningSystem.h"
#include "../components/Components.h"
#include <iostream>
#include <chrono>

MobSpawningSystem::MobSpawningSystem(EntityFactory *factory, float screenW, float screenH)
    : entityFactory(factory), timeSinceLastSpawn(0.0f), spawnInterval(0.5f),
      screenWidth(screenW), screenHeight(screenH),
      randomGenerator(std::chrono::steady_clock::now().time_since_epoch().count()),
      mobTypeDistribution(0, 2), // 0-2 for 3 mob types
      positionDistribution(0.0f, 1.0f),
      speedDistribution(0.0f, 1.0f)
{
}

void MobSpawningSystem::update(ECS &ecs, GameManager &gameManager, float deltaTime)
{
    // Only spawn mobs during gameplay
    if (gameManager.currentState != GameManager::PLAYING)
    {
        return;
    }

    // Update spawn timer
    timeSinceLastSpawn += deltaTime;

    // Check if it's time to spawn a new mob
    if (timeSinceLastSpawn >= spawnInterval)
    {
        spawnMob(ecs);
        timeSinceLastSpawn = 0.0f;

        // Gradually decrease spawn interval to increase difficulty
        if (spawnInterval > 0.2f)
        {
            spawnInterval = std::max(0.2f, spawnInterval - 0.01f);
        }
    }
}

void MobSpawningSystem::spawnMob(ECS &ecs)
{
    // Choose random mob type
    int mobTypeIndex = mobTypeDistribution(randomGenerator);
    std::string mobType = mobTypes[mobTypeIndex];

    // Get mob configuration
    json mobConfig = entityFactory->getEntityConfig()["mobs"][mobType];

    // Create mob entity
    EntityID mobEntity = ecs.createEntity();

    // Add MobTag component
    ecs.addComponent(mobEntity, MobTag{});

    // Add EntityType component for texture identification
    ecs.addComponent(mobEntity, EntityType{mobType});

    // Determine spawn position (always spawn from the right side)
    float spawnX = screenWidth + 50.0f;                                                     // Start off-screen to the right
    float spawnY = positionDistribution(randomGenerator) * (screenHeight - 100.0f) + 50.0f; // Random Y within screen bounds

    // Create Transform component
    Transform transform;
    transform.x = spawnX;
    transform.y = spawnY;
    transform.rotation = 0.0f;
    ecs.addComponent(mobEntity, transform);

    // Create Sprite component
    json spriteConfig = mobConfig["sprite"];
    Sprite sprite;
    sprite.texture = nullptr; // Will be loaded by ResourceManager in RenderSystem
    sprite.width = spriteConfig["width"].get<int>();
    sprite.height = spriteConfig["height"].get<int>();
    sprite.frameCount = spriteConfig["frameCount"].get<int>();
    sprite.frameTime = spriteConfig["frameTime"].get<float>();
    sprite.animated = spriteConfig["animated"].get<bool>();
    ecs.addComponent(mobEntity, sprite);

    // Create Animation component if animated
    if (spriteConfig["animated"].get<bool>())
    {
        Animation animation;
        animation.currentFrame = 0;
        animation.animationTimer = 0.0f;
        ecs.addComponent(mobEntity, animation);
    } // Create Collider component
    json colliderConfig = mobConfig["collider"];
    Collider collider;
    collider.width = colliderConfig["width"].get<float>();
    collider.height = colliderConfig["height"].get<float>();
    collider.isTrigger = colliderConfig["isTrigger"].get<bool>();
    ecs.addComponent(mobEntity, collider);

    // Create Velocity component (normalized direction vector)
    Velocity velocity;
    velocity.x = -1.0f; // Move left (normalized direction)
    velocity.y = 0.0f;
    ecs.addComponent(mobEntity, velocity);

    // Create Speed component (random speed within range)
    json speedRange = mobConfig["speedRange"];
    float minSpeed = speedRange["min"].get<float>();
    float maxSpeed = speedRange["max"].get<float>();
    float speed = minSpeed + speedDistribution(randomGenerator) * (maxSpeed - minSpeed);

    Speed speedComponent;
    speedComponent.value = speed;
    ecs.addComponent(mobEntity, speedComponent);

    std::cout << "Spawned " << mobType << " mob at (" << spawnX << ", " << spawnY << ") with speed " << speed << std::endl;
}
