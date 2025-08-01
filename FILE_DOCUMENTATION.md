# C++ ECS Implementation - File Documentation

This document explains the function and purpose of each file in the C++ ECS version of "Dodge the Creeps".

## 📁 Project Structure Overview

```
cpp_version/
├── src/                    # Source code
│   ├── main.cpp           # Entry point
│   ├── components/        # ECS Component definitions
│   ├── core/             # Core game engine classes
│   ├── managers/         # Resource and entity management
│   └── systems/          # ECS System implementations
├── art/                  # Game assets (sprites, audio, fonts)
├── build/               # Build output directory
├── entities.json        # Entity configuration data
├── CMakeLists.txt       # Build configuration
└── run.sh              # Build and run script
```

## 🎯 Entry Point

### `main.cpp`

**Purpose**: Application entry point and main game loop initialization

- **Function**: Creates Game instance, initializes it, runs the main loop, and handles shutdown
- **Dependencies**: core/Game.h
- **Key Responsibilities**:
  - Game object creation and lifecycle management
  - Error handling for initialization failures
  - Clean exit handling

## 🧠 Core Engine

### `core/Game.h` & `core/Game.cpp`

**Purpose**: Main game class that orchestrates all systems and manages the game loop

- **Function**: Central coordinator for the entire game architecture
- **Key Responsibilities**:
  - SDL2 initialization and window/renderer management
  - ECS and system initialization in proper order
  - Game state management (Menu, Playing, GameOver)
  - Main game loop with fixed timestep
  - System update coordination
  - Resource cleanup and shutdown
- **Dependencies**: All systems, managers, ECS, SDL2 libraries

### `core/ECS.h`

**Purpose**: Entity Component System foundation

- **Function**: Provides the core ECS architecture with entity, component, and system management
- **Key Responsibilities**:
  - Entity ID generation and management
  - Component storage and retrieval
  - Entity lifecycle (creation, destruction)
  - Component-entity associations
  - Memory management for components

## 🔧 Components

### `components/Components.h`

**Purpose**: Defines all data components used in the ECS architecture

- **Function**: Pure data structures that hold entity state
- **Key Components**:
  - `Transform`: Position (x, y) and rotation
  - `Velocity`: Movement vector (x, y)
  - `Sprite`: Texture, dimensions, animation data, current texture path
  - `Animation`: Frame tracking, timing, sprite flipping
  - `PlayerTag`/`MobTag`: Entity type identification
  - `MovementDirection`: Directional movement state for sprite facing
  - `UIText`: Text rendering data (font, color, content)
  - `UIPosition`: UI element positioning

## 🎮 Systems

### `systems/System.h`

**Purpose**: Base interface for all ECS systems

- **Function**: Defines common system interface and update pattern
- **Key Responsibilities**:
  - Pure virtual update method
  - ECS reference storage
  - Common system lifecycle

### `systems/Systems.h`

**Purpose**: Includes all system headers for convenient importing

- **Function**: Single include point for all game systems

### `systems/InputSystem.h` & `systems/InputSystem.cpp`

**Purpose**: Handles all player input and game state transitions

- **Function**: Processes keyboard input and translates to game actions
- **Key Responsibilities**:
  - Player movement input (WASD/Arrow keys)
  - Game state transitions (start game, restart)
  - Velocity updates based on input
  - Mob cleanup on game restart
- **Used By**: Game main loop for input processing

### `systems/MovementSystem.h` & `systems/MovementSystem.cpp`

**Purpose**: Applies physics movement to all entities with Transform and Velocity

- **Function**: Updates entity positions based on velocity and delta time
- **Key Responsibilities**:
  - Frame-rate independent movement (velocity × speed × deltaTime)
  - Position updates for all moving entities
  - Movement calculation consistency
- **Used By**: Game loop for physics updates

### `systems/AnimationSystem.h` & `systems/AnimationSystem.cpp`

**Purpose**: Manages sprite animations and directional facing

- **Function**: Updates animation frames and handles sprite direction changes
- **Key Responsibilities**:
  - Animation frame progression based on timing
  - Sprite texture updates for animated entities
  - Directional sprite flipping based on movement
  - Animation loop management
- **Used By**: Game loop before rendering

### `systems/RenderSystem.h` & `systems/RenderSystem.cpp`

**Purpose**: Renders all visual elements (sprites, UI text, backgrounds)

- **Function**: Handles all SDL2 rendering operations
- **Key Responsibilities**:
  - Background rendering (sky blue color)
  - Sprite rendering with optional flipping
  - UI text rendering with proper positioning
  - SDL2 render pipeline management
  - Texture loading and management for animations
- **Used By**: Game loop for visual output

### `systems/CollisionSystem.h` & `systems/CollisionSystem.cpp`

**Purpose**: Detects collisions between player and enemies

- **Function**: AABB collision detection for game over conditions
- **Key Responsibilities**:
  - Player-mob collision detection
  - Game state transition to GameOver
  - Collision response handling
- **Used By**: Game loop for gameplay mechanics

### `systems/BoundarySystem.h` & `systems/BoundarySystem.cpp`

**Purpose**: Manages screen boundaries and entity cleanup

- **Function**: Keeps player on screen and removes off-screen enemies
- **Key Responsibilities**:
  - Player boundary constraint (within screen bounds)
  - Off-screen enemy cleanup for performance
  - Screen edge detection
- **Used By**: Game loop for boundary management

### `systems/MobSpawningSystem.h` & `systems/MobSpawningSystem.cpp`

**Purpose**: Creates enemy entities at regular intervals from all screen edges

- **Function**: Manages enemy spawning logic and timing
- **Key Responsibilities**:
  - Timer-based enemy spawning
  - Multi-directional spawning (all four screen edges)
  - Random enemy type selection from JSON configuration
  - Proper velocity and direction assignment
  - Spawn rate management based on game progression
- **Used By**: Game loop during Playing state

### `systems/AudioSystem.h` & `systems/AudioSystem.cpp`

**Purpose**: Manages background music and sound effects

- **Function**: Controls all audio playback using SDL2_mixer
- **Key Responsibilities**:
  - Background music looping
  - Sound effect playback (game over, etc.)
  - Audio resource management
  - Volume and audio state control
- **Used By**: Game loop and collision system

### `systems/TimingSystem.h` & `systems/TimingSystem.cpp`

**Purpose**: Manages game timing, delta time calculation, and score updates

- **Function**: Provides timing services and score progression
- **Key Responsibilities**:
  - Delta time calculation for frame-rate independence
  - Score progression (10 points per second)
  - Game timing coordination
  - Time-based game mechanics support
- **Used By**: All systems requiring timing information

## 🗃️ Managers

### `managers/ResourceManager.h` & `managers/ResourceManager.cpp`

**Purpose**: Centralized loading and caching of textures and fonts

- **Function**: Asset loading, caching, and memory management
- **Key Responsibilities**:
  - Texture loading with SDL2_image and caching
  - Font loading with SDL2_ttf and size management
  - Text texture creation from fonts
  - Resource cleanup and memory management
  - Asset path management with ASSET_PATH prefix
- **Used By**: RenderSystem, AnimationSystem, EntityFactory

### `managers/EntityFactory.h` & `managers/EntityFactory.cpp`

**Purpose**: Creates game entities based on JSON configuration

- **Function**: Entity creation and component assignment from data files
- **Key Responsibilities**:
  - JSON parsing for entity definitions
  - Player entity creation with all required components
  - Enemy entity creation with random type selection
  - UI element creation (score, game over text)
  - Component initialization and configuration
- **Used By**: Game initialization, MobSpawningSystem

### `managers/GameManager.h`

**Purpose**: Central game state and data management

- **Function**: Maintains game state, score, and global game data
- **Key Responsibilities**:
  - Game state enumeration (Menu, Playing, GameOver)
  - Score tracking with fractional accumulation
  - Game state transitions
  - Global game configuration and constants
- **Used By**: All systems requiring game state information

## 📄 Configuration

### `entities.json`

**Purpose**: Data-driven entity configuration

- **Function**: Defines entity templates, game settings, and UI configurations
- **Key Data**:
  - Player entity configuration (sprites, speed, animation)
  - Enemy entity types with variations
  - UI text configurations and positioning
  - Game constants and spawn parameters
- **Used By**: EntityFactory for entity creation

### `CMakeLists.txt`

**Purpose**: Build system configuration

- **Function**: Defines compilation targets, dependencies, and build settings
- **Key Responsibilities**:
  - SDL2 library linking
  - Include path configuration
  - Executable target definition
  - Compiler flags and standards

### `run.sh`

**Purpose**: Build and execution automation script

- **Function**: Simplified build and run process
- **Key Responsibilities**:
  - Directory creation and build execution
  - CMake configuration and make execution
  - Automatic game launch after successful build

## 🎨 Assets

### `art/` Directory

**Purpose**: Contains all game assets

- **Function**: Stores sprites, audio, and font files
- **Contents**:
  - Player sprites (walk animations, directional facing)
  - Enemy sprites (flying, swimming, walking types)
  - Audio files (background music, sound effects)
  - Font files for UI text rendering
- **Used By**: ResourceManager for asset loading

## 🔄 System Interaction Flow

1. **Initialization**: Game → ECS → Systems → ResourceManager → EntityFactory
2. **Game Loop**:
   - TimingSystem (delta time calculation)
   - InputSystem (player input processing)
   - MobSpawningSystem (enemy creation)
   - MovementSystem (physics updates)
   - AnimationSystem (sprite updates)
   - CollisionSystem (collision detection)
   - BoundarySystem (boundary enforcement)
   - AudioSystem (audio management)
   - RenderSystem (visual output)
3. **Shutdown**: Game → Systems cleanup → SDL2 cleanup

## 🎯 Architecture Benefits

- **Modularity**: Each system handles a specific concern
- **Data-Driven**: JSON configuration allows easy tweaking
- **Performance**: ECS architecture optimizes cache usage
- **Maintainability**: Clear separation of responsibilities
- **Extensibility**: Easy to add new components and systems

This documentation provides a complete understanding of how each file contributes to the overall C++ ECS game architecture.
