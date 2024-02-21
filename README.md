<h1 align="center"> Elven Engine 
<br/>
  
[![Build](https://github.com/denyskryvytskyi/ElvenEngine/actions/workflows/cmake.yml/badge.svg)](https://github.com/denyskryvytskyi/ElvenEngine/actions/workflows/cmake.yml)
[![CodeQL](https://github.com/denyskryvytskyi/ElvenEngine/actions/workflows/codeql.yml/badge.svg)](https://github.com/denyskryvytskyi/ElvenEngine/actions/workflows/codeql.yml)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/denyskryvytskyi/ElvenEngine/blob/master/LICENSE)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/493f09fda55b43f68886f52be5240d27)](https://www.codacy.com/gh/denyskryvytskyi/ElvenEngine/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=denyskryvytskyi/ElvenEngine&amp;utm_campaign=Badge_Grade)

  
</h1>

Elven Engine is primarily a 2D/3D game engine that is being developed from scratch.

## Getting Started

Windows platform only support for now (Linux and MacOS platforms are for future support)

You can clone the repository using git (**`--recursive`** is required to fetch all of the submodules):

`git clone --recursive https://github.com/kryvytskyidenys/ElvenEngine`

Firstly you need to install [cmake](https://cmake.org/) 3.10+ version (3.21+ for VS 2022 support).

### Windows
1. Configure and build third-party libraries: `scripts/setup-vendor.bat`
2. Configure Visual Studio solution for the Engine and Game/Example projects: `scripts/configure-vs2022`.
    
    2.1. Or run a command from the build directory with your generator and architecture: `cmake -G "Visual Studio Generator 17 2022" -A x64`
3. Build a solution (if you want to build using cmake) for both Debug and Release config (pass it as an argument): `scripts/build.bat`

## Features
+ [x] Logging system
+ [x] Event system (non-blocking event queue-based system)
+ [x] Custom math library ([lia](https://github.com/denyskryvytskyi/lia))
+ [x] Renderer core (graphics API agnostic)
  - [x] Shaders loading
  - [x] Async textures loading
  - [x] Buffers, Shader, Texture abstractions
  - [x] Camera (orthographic, perspective)
  - [x] DSA OpenGL Renderer implementation
  - [x] Fullscreen switch support
+ [ ] 2D Renderer
  - [x] Quad rendering
  - [x] Texture rendering
  - [x] Batch rendering (quad and texture)
  - [x] Text Rendering
  - [ ] Spritesheet animation
+ [x] ECS
  - [x] Data-oriented cache-friendly components system architecture
  - [x] In-Engine components: Transform, Sprite, Text, Quad, Camera, RectTransform
  - [x] Components serialization
  - [x] Behavior component as the entity brain
  - [x] Optional Systems for usability
  - [x] Scene as the ECS coordinator
  - [x] Scene serialization
+ [x] Data-driven architecture
  - [x] Load/Save engine settings from/to JSON files
+ [x] Sound engine
  - [x] Support formats: mp3, wav, ogg, flac etc.
  - [x] Add/Play/Pause/Stop functionality
+ [x] Just cool stuff
  - [x] Orthographic camera controller (OrthographicCameraController), that can be used if needed
  - [x] Fly(FPS-like) 3D camera support (CameraController)
+ [ ] 3D Renderer
  - [ ] Mesh/Model system
  - [ ] Primitives: cube, sphere, plane
  - [ ] Model loading (Assimp)
  - [ ] Lighting support
+ [ ] In-engine editor (based on ImGui)
  - [ ] Scene hierarchy
  - [ ] Properties: entity components
  - [ ] Graphics stats
+ [ ] Multithreading support
  - [ ] Thread pool

## Demo
#### Space Invaders
<b>Quick demo</b>

<img src=".github/demo/invaders.gif">

<b>Full demo</b>

https://github.com/denyskryvytskyi/ElvenEngine/assets/25298585/f0d32c8b-1ed2-44e3-9c93-a781f3da4203

#### Ping-pong
<img src=".github/demo/pong.gif">

#### TRON
<img src=".github/demo/tron.gif">

#### Sprite rendering
<img src=".github/demo/fantasy.png" width="80%">

#### Quad and texture batch rendering (20000 wizards)
<img src=".github/demo/wizards.gif">

#### 3D rendering
<img src=".github/demo/cubes.gif">

## Third-party libraries
| Lib |  |
| ------ | ------ |
| [cmake](https://github.com/Kitware/CMake) | build system |
| [spdlog](https://github.com/gabime/spdlog) | header-only logging library |
| [GLFW](https://github.com/glfw/glfw) | windows, OpenGL contexts and handle input |
| [glad 2](https://glad.dav1d.de/) | OpenGL loader |
| [lia](https://github.com/kryvytskyidenys/lia) | my custom math library |
| [ImGui](https://github.com/kryvytskyidenys/imgui) | library using for GUI (visual-editor) |
| [stb image](https://github.com/nothings/stb/blob/master/stb_image.h) | image loader |
| [json](https://github.com/nlohmann/json) | json lib for serialization and data-driven architecture |
| [irrKlang](https://www.ambiera.com/irrklang/) | sound library |
| [fmt](https://github.com/fmtlib/fmt) | formatting library |
| [freetype]([https://github.com/fmtlib/fmt](https://freetype.org/)) | fonts rendering |
