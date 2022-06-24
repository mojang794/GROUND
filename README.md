# GROUND

a 3D game

## What does it will containts?
- [x] ECS(Entity Components System)
- [x] 3D Support
- [x] Camera support
- [x] Shading support
- [x] Basic OpenGL
- [ ] Joystick support
- [ ] Full Audio Support

# Engine

### audio
- Sound2D
- Sound3D
- Music // Work in progress
### system
- Vertex
- Color
- Collision // Work in progress...
- StateMachine
### graphics
- 3D model load function (ONLY OBJ AT THE MOMENT: they need Triangles, UV and Normals)
- Predefined shapes
- Shader class
- VAO class
- VBO class
- Texture class
- FrameBuffer class
- 3D Camera class
### utils
- Mathematic/util header
- Simple Config file parser
# Libraries used in this project
Graphic Libraries:
- glad(Windows) / glew(Linux)
- GLFW3
- freetype (For text display using OpenGL)
- Dear ImGui

Audio Libraries:
- Soft OpenAL
- sndfile

Data/Mathematic Libraries:
- GLM
- stb_image