cmake_minimum_required(VERSION 3.13)
project(RenderGU)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS " -Wall -Werror")

include_directories(src)
include_directories(../Libs/Libs/glm)
include_directories(../Libs/Libs/glad/include)


add_executable(RenderGU
        ${CMAKE_SOURCE_DIR}/../Libs/Libs/glad/src/glad.c
        src/CompileShaders.h
        src/CustomMatrices.h
        src/data.h
        src/input.h
        src/LinkShaders.h
        src/main.cpp
        src/Rendering.h
        src/Shaders.h
        src/stb_image.h
        src/Textures.h
        src/Utility.h
        src/VertexSpecification_Common.h
        src/Camera.h
        src/Window.h
        src/models/floor/model.h
        src/models/floor/shaders.h
        src/models/simple_quad/model.h
        src/models/simple_quad/shaders.h
        src/Rendering_Common.h
        src/scenes/CubeGrassWindowFloor/scene_render.h
        src/scenes/Skybox/scene_render.h
        src/models/skybox/model.h
        src/models/skybox/shaders.h
        src/scenes/Skybox/setup_cubemap.h
        src/models/cube/model.h
        src/models/cube/shaders.h)


target_link_libraries(RenderGU LINK_PUBLIC glfw)
target_link_libraries(RenderGU LINK_PUBLIC GL)
target_link_libraries(RenderGU LINK_PUBLIC X11)
target_link_libraries(RenderGU LINK_PUBLIC pthread)
target_link_libraries(RenderGU LINK_PUBLIC Xrandr)
target_link_libraries(RenderGU LINK_PUBLIC Xi)
target_link_libraries(RenderGU LINK_PUBLIC Xxf86vm)
target_link_libraries(RenderGU LINK_PUBLIC Xinerama)
target_link_libraries(RenderGU LINK_PUBLIC Xcursor)
target_link_libraries(RenderGU LINK_PUBLIC dl)
