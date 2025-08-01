# Dodge the Creeps - Godot vs C++ ECS Comparison

This project demonstrates the implementation of the same 2D game "Dodge the Creeps" using two different approaches:

## 📁 Project Structure

### `gamedot_version/` - Godot Implementation

- **Engine**: Godot 4.x
- **Language**: GDScript
- **Architecture**: Scene-based, Node hierarchy
- **Features**: Built-in physics, animation, audio, and UI systems

### `cpp_version/` - C++ ECS Implementation

- **Language**: C++ with SDL2
- **Architecture**: Pure Entity Component System (ECS)
- **Features**: Custom systems for rendering, physics, audio, and UI
- **Libraries**: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, nlohmann/json

## 🎮 Game Features

Both versions implement the same core gameplay:

- **Player Movement**: Arrow keys or WASD to move
- **Enemy Spawning**: Creatures spawn from all screen edges with random types and speeds
- **Collision Detection**: Game over when player touches any enemy
- **Scoring System**: Points increase over time (10 points per second)
- **Game States**: Menu → Playing → Game Over → Restart cycle
- **Visual Effects**: Directional sprites, animations, sky blue background
- **Audio**: Background music and sound effects

## 🔧 How to Run

### Godot Version

1. Open the `gamedot_version/` folder in Godot
2. Press F5 to run the project

### C++ ECS Version

1. Navigate to the `cpp_version/` folder
2. Run the build script: `./run.sh`
3. Or manually build: `mkdir -p build && cd build && cmake .. && make && cd .. && ./build/DodgeTheCreeps`

## 🏗️ Architecture Comparison

### Godot (Scene-Based)

```
Main Scene
├── Player (CharacterBody2D)
├── MobSpawner (Timer + spawning logic)
├── HUD (UI overlay)
└── Audio (AudioStreamPlayer)
```

### C++ ECS (Pure Component System)

```
Systems:
├── InputSystem (handles player movement)
├── MovementSystem (applies velocity * speed * deltaTime)
├── AnimationSystem (updates sprite frames)
├── MobSpawningSystem (creates enemies from JSON config)
├── CollisionSystem (AABB collision detection)
├── BoundarySystem (screen bounds + cleanup)
├── RenderSystem (sprite + UI rendering)
└── AudioSystem (music + SFX management)

Components:
├── Transform, Velocity, Sprite, Animation
├── PlayerTag, MobTag, EntityType
├── UIText, UIPosition
└── MovementDirection (for directional sprites)
```

## 📊 Key Differences

| Aspect                | Godot                                  | C++ ECS                              |
| --------------------- | -------------------------------------- | ------------------------------------ |
| **Development Speed** | Fast (visual editor, built-in systems) | Slower (custom implementation)       |
| **Performance**       | Good (optimized engine)                | Excellent (custom optimized systems) |
| **Memory Usage**      | Higher (engine overhead)               | Lower (minimal dependencies)         |
| **Flexibility**       | Moderate (engine constraints)          | High (full control)                  |
| **Debugging**         | Built-in debugger, inspector           | Custom logging, external tools       |
| **Asset Pipeline**    | Automatic import/management            | Manual resource loading              |
| **Code Organization** | Scene hierarchy + scripts              | Pure ECS architecture                |

## 🎯 Learning Outcomes

This comparison demonstrates:

- **Godot's Strengths**: Rapid prototyping, visual workflow, comprehensive built-in systems
- **C++ ECS Advantages**: Performance optimization, architectural flexibility, educational value
- **Trade-offs**: Development time vs. control, ease-of-use vs. customization

## � Documentation

- **[FILE_DOCUMENTATION.md](FILE_DOCUMENTATION.md)**: Detailed explanation of each file's function and purpose in the C++ ECS implementation
- **Architecture Overview**: See the comparison table above for high-level differences between approaches

## 🛠️ Technical Highlights

### C++ ECS Implementation Features

- Pure Entity Component System architecture with data-driven design
- JSON-based entity configuration for easy modification
- Frame-rate independent movement and gameplay
- Multi-directional enemy spawning with proper sprite facing
- Custom resource management and memory optimization

---

**Created for educational purposes to compare game engine approaches and architectural patterns.**
