# 3D GLFW Game Project

A C++ 3D graphics engine built from scratch using OpenGL, GLFW, and GLM. Designed as a foundation for 3D game development with modular architecture and physics integration.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Development Progress](#development-progress)
- [Project Structure](#project-structure)
- [Setup and Installation](#setup-and-installation)
  - [Prerequisites](#prerequisites)
  - [Library Installation](#library-installation)
  - [Building](#building)
- [Usage](#usage)
- [Architecture](#architecture)
- [Git Workflow](#git-workflow)
- [Roadmap](#roadmap)
- [License](#license)
- [Contact and Support](#contact-and-support)

---

## Overview

This project is (FOR NOW) a custom 3D graphics engine built with **C++14** and **OpenGL 3.3 (Core Profile)**. 
It provides a foundational framework for a potential future game project:
- Real-time 3D rendering
- Camera control with freelook
- Player physics (gravity, jumping, sprinting)
- Scene management
- Input handling
- Easy object and mesh generation

**Target**: A modular, expandable engine suitable for indie game prototyping and personal analysis / education.

---

## Features

### Core Systems
- **OpenGL Rendering**: Modern OpenGL 3.3+ with shader support
- **Camera System**: Freelook with yaw/pitch, smooth mouse damping
- **Input Management**: Keyboard and mouse input with proper state tracking (controller support planned)
- **Scene Management**: Pluggable scene architecture with lifecycle hooks (upcoming menu system)
- **Entity-Component System**: Foundation for game objects (Player, interactables)

### Player Mechanics
- **Physics**: Gravity, jumping, terminal velocity
- **Movement**: Camera-relative WASD (horizontal only) with acceleration/friction
- **Sprint**: Shift multiplier (1.8x speed)
- **Flight Mode**: Toggle-able flying with vertical Space/Ctrl controls
- **Ground Detection**: Simple plane collision with configurable ground Y

### Graphics
- **Multiple Mesh Types**: Triangles, squares, cubes, cube edges (how to combine last two?)
- **Grid Shader**: Procedural grid floor rendering
- **Basic Lighting**: Per-object color (foundation for Physically Based Rendering later)

---

## Development Progress

### Week 1: Core Engine & Player Control

**Commits & Milestones:**

#### Phase 1: Engine Foundation
- **Input System**: Implemented `Input` class with GLFW integration (handles `GLFW_REPEAT` for held keys)
- **Camera System**: Built `Camera` with freelook (yaw/pitch), mouse sensitivity, and smooth damping
- **Scene Management**: Created `SceneManager` and base `Scene` class with lifecycle (`onEnter`, `onExit`)

#### Phase 2: Player Physics & Movement
- **Entity Base Class**: Added `Entity` with position, velocity, gravity scale, and flying flag
- **Player Class**: Derived from `Entity` with full physics:
  - Gravity integration (`-9.81 m/s²` with configurable scale)
  - Jump impulse and terminal velocity clamping
  - Ground detection and snapping
- **Movement Controller**: Camera-relative horizontal movement (WASD flattened to XZ plane)
  - Acceleration/deceleration smoothing
  - Friction-based sliding on input release
  - Sprint multiplier (Shift key)
  - Vertical controls: Jump (grounded) / Flight (Space/Ctrl when flying)

#### Phase 3: Integration & Polish
- **Input Refactoring**: Replaced per-frame key array with direct `Input` queries to avoid temporary allocations
- **Camera Getters**: Added `getFront()`, `getRight()`, `getUp()` for physics queries
- **Micro-optimizations**: Changed `glm::length()` to `glm::length2()` for zero-checks, cached trigonometry in camera updates
- **Scene Setup**: Fixed initialization order (resources set before `setupSceneObjects()`)

**Testing:**
- TODO: Add unit tests for physics calculations and input handling
- TODO: Needs error handling class

---

## Project Structure

```
3D_GLFW_FIRST/
├── include/
│   ├── core/
│   │   └── input.h              # Input state management
│   ├── rendering/
│   │   ├── camera.h             # Freelook camera system
│   │   ├── shader.h             # Shader compilation & uniforms
│   │   ├── renderer.h           # Render commands
│   │   └── mesh.h               # Mesh data & draw calls
│   ├── scenes/
│   │   ├── scene.h              # Scene base class
│   │   ├── scenemanager.h       # Scene lifecycle management
│   │   ├── gamescene.h          # Main game scene
│   │   └── sceneobject.h        # Renderable objects
│   └── ecs/
│       ├── entity.h             # Base entity (physics, state)
│       └── player.h             # Player-specific implementation
├── src/
│   ├── core/
│   │   └── input.cpp
│   ├── rendering/
│   │   ├── camera.cpp
│   │   ├── shader.cpp
│   │   ├── renderer.cpp
│   │   └── mesh.cpp
│   ├── scenes/
│   │   ├── scenemanager.cpp
│   │   ├── gamescene.cpp
│   │   └── sceneobject.cpp
│   ├── ecs/
│   │   ├── entity.cpp
│   │   └── player.cpp
│   └── main.cpp                 # Engine game loop and initialization
├── shaders/
│   ├── basic.vert               # Standard vertex shader
│   ├── basic.frag               # Standard fragment shader
│   └── grid.frag                # Procedural grid floor shader
└── README.md
```
---

# Setup and Installation

### Prerequisites

- **Visual Studio 2022** (or compatible C++14 compiler)
- **Git**
- Windows 10/11 (x64)
- GLAD, GLFW3, GLM libraries (see below)

### Library Installation

## 1. GLFW3 (Window & Input)
Download precompiled GLFW from https://www.glfw.org/download.html
Extract to a known location, e.g., C:\Libraries\GLFW

#### In Visual Studio Project Properties:
- VC++ Directories > Include Directories: Add C:\Libraries\GLFW\include
- VC++ Directories > Library Directories: Add C:\Libraries\GLFW\lib-vc2022
- Linker > Input > Additional Dependencies: Add glfw3.lib
- Copy C:\Libraries\GLFW\lib-vc2022\glfw3.dll to your Debug/Release folders

## 2. GLAD (OpenGL Loader)
Go to https://glad.dav1d.de/
Select OpenGL 3.3 (Core Profile)
Download and extract

## 3. GLM (Math Library)
Clone or download from https://github.com/g-truc/glm
Extract to C:\Libraries\GLM (or similar)

#### In Visual Studio Project Properties:
- VC++ Directories > Include Directories: Add <path-to-glad>\include
- Add glad.c to your project source files
- VC++ Directories > Include Directories: Add C:\Libraries\GLM
(GLM is header-only, no linking required)

### Building

```bash
git clone https://github.com/TomBlob/GLFW_GAME.git
cd GLFW_GAME
# Open 3D_GLFW_FIRST.sln in Visual Studio
# Build > Build Solution (Ctrl+Shift+B)
# Debug > Start Debugging (F5)
```

---

## Usage

### Controls

| Input | Action |
|-------|--------|
| **W / A / S / D** | Move forward/left/backward/right (horizontal only) |
| **Space** | Jump (grounded) / Ascend (flying) |
| **Left Ctrl** | Descend (flying only) |
| **Left Shift** | Sprint (1.8x speed multiplier) |
| **Mouse** | Look around (pitch/yaw) |
| **Esc** | Close application |

### Toggling Flight Mode

Flight mode is currently controlled by the `Player::flying` flag. To toggle it at runtime:
```cpp
// In main.cpp or via a key binding
player.flying = !player.flying;
```

---

# Architecture

## ECS (Entity Component System)

**Base Entity:**
- Stores position, velocity, gravity scale, flying flag
- Provides virtual `update(deltaTime)` for derived classes

**Player (extends Entity):**
- Handles input (`handleInput()`)
- Applies physics (`update()`)
- Configurable: moveSpeed, acceleration, jumpImpulse, terminalSpeed


## Scene Management

**SceneManager:**
- Registers and loads scenes by name
- Manages lifecycle (`onEnter()` → `onExit()`)
- Keeps track of active scene and camera

**GameScene:**
- Holds game objects (entities, meshes)
- Manages rendering loop
- Receives shared resources (meshes, shaders) from main

## Camera System

**Features:**
- **Freelook**: Yaw/pitch controlled by mouse
- **Damping**: Smooth decay of mouse velocity (configurable `mouseDamping`)
- **Sensitivity**: Adjustable mouse sensitivity
- **Getters**: `getFront()`, `getRight()`, `getUp()` for physics integration

---

## Git Workflow

### Branch Strategy

```
master          (stable, production-ready)
  ↑
dev             (integration branch for features)
  ↑
feat-XYZ        (feature branches, created from dev)
```

### Line Endings

To avoid line ending issues on Windows:
```
git config --global core.autocrlf true
```


## Roadmap

### Upcoming (Week 2+)
- [ ] Assets loading (models, textures)
- [ ] Mesh collision detection
- [ ] Ray casting for interaction
- [ ] Menu system with UI
- [ ] Player GUI base

---

## License

This project and its code are proprietary and confidential. 
Unauthorized copying, distribution, or use is strictly prohibited.

© 2026 Thomas Primeau. All rights reserved.

---

## Contact and Support

- **GitHub**: [TomBlob](https://github.com/TomBlob)
- **Repository**: [GLFW_GAME](https://github.com/TomBlob/GLFW_GAME)

---

**Last Updated**: May 16, 2026 | **Current Version**: 0.1.0 (Week 1 - Core Engine)

