cmake_minimum_required(VERSION 3.13)
project(RenderGU)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS " -Wall -Werror")

include_directories(${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src)
include_directories(../../Libs/Libs/glm)
include_directories(../../Libs/Libs/glad/include)


add_executable(RenderGU
        ${CMAKE_SOURCE_DIR}/../../Libs/Libs/glad/src/glad.c
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/CompileShaders.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/CustomMatrices.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/data.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/input.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/LinkShaders.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/main.cpp
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Rendering.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Shaders.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/stb_image.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Textures.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Utility.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/VertexSpecification_Common.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Camera.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Window.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/floor/model.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/floor/shaders.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/simple_quad/model.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/simple_quad/shaders.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/Rendering_Common.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/scenes/CubeGrassWindowFloor/scene_render.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/scenes/Skybox/scene_render.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/skybox/model.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/skybox/shaders.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/scenes/Skybox/setup_cubemap.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/cube/model.h
        ${CMAKE_SOURCE_DIR}/../Eclipse/Projects/src/models/cube/shaders.h)


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
