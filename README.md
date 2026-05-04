
---
# 3D GLFW GAME PROJECT
---

\
This project is built with visual studio 2022, and uses the following libraries:

- GLFW3.lib (window management and input handling)
- GLAD.lib (openGL loader)

### For dll link and include installation :
- add precompiled GLFW files to general include folder (needs \include and \lib-vc2022)
- add include header paths in Additional Include Directories (ex: C:\Libraries\GLFW\include)
- add lib folder paths in Linker's Additional Library Directories (ex: C:\Libraries\GLFW\lib-vc2022)
- link library (glfw3.lib) to Linker's input (additional dependencies)
- copy .dll files to executable folder (Debug and Release)
- test !

### GLAD (openGL loader) installation:

- go to https://glad.dav1d.de/ and select appropriate options
- add include and src files to project
- add include header paths in Additional Include Directories (ex: C:\Libraries\GLAD\include)

### GLM (openGL mathematics library) installation:

- clone repo from GitHub in include folder outside project
- add include header paths in Additional Include Directories

### GitHub branches:

- master: stable version of the project, with all features implemented and tested
- dev: branch for new features and bug fixes, may be unstable
- feature/branch-name: branches for specific features or bug fixes, created from development branch and merged back when complete

