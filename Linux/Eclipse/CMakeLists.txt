cmake_minimum_required(VERSION 3.21)
project(Eclipse)

set(CMAKE_CXX_STANDARD 14)

include_directories(Projects/src)
include_directories(../../Libs/Libs/glm)
include_directories(../../Libs/Libs/glad/include)
include_directories(../../Libs/Libs/glfw-3.3.4-x86/include)

link_directories(../../Libs/Libs/glad/lib/Debug/linux/)
link_directories(/home/philippe/Downloads/glfw-3.1.2/cmake-build-debug/src)

add_executable(Eclipse
        Projects/src/CompileShaders.h
        Projects/src/CustomMatrices.h
        Projects/src/data.h
        Projects/src/input.h
        Projects/src/LinkShaders.h
        Projects/src/main.cpp
        Projects/src/Rendering.h
        Projects/src/Shaders.h
        Projects/src/stb_image.h
        Projects/src/Textures.h
        Projects/src/Utility.h
        Projects/src/VertexSpecification_Common.h
        Projects/src/Camera.h
        Projects/src/Window.h
        Projects/src/models/floor/model.h
        Projects/src/models/floor/shaders.h
        Projects/src/models/simple_quad/model.h
        Projects/src/models/simple_quad/shaders.h
        Projects/src/Rendering_Common.h
        Projects/src/scenes/CubeGrassWindowFloor/render.h Projects/src/scenes/Skybox/render.h Projects/src/models/simple_cube/model.h Projects/src/models/simple_cube/shaders.h)


target_link_libraries(Eclipse LINK_PUBLIC libglad_build.a)
target_link_libraries(Eclipse LINK_PUBLIC glfw3)
target_link_libraries(Eclipse LINK_PUBLIC GL)
target_link_libraries(Eclipse LINK_PUBLIC X11)
target_link_libraries(Eclipse LINK_PUBLIC pthread)
target_link_libraries(Eclipse LINK_PUBLIC Xrandr)
target_link_libraries(Eclipse LINK_PUBLIC Xi)
target_link_libraries(Eclipse LINK_PUBLIC Xxf86vm)
target_link_libraries(Eclipse LINK_PUBLIC Xinerama)
target_link_libraries(Eclipse LINK_PUBLIC Xcursor)
target_link_libraries(Eclipse LINK_PUBLIC dl)
