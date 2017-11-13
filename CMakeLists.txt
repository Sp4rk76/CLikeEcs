#CMake: required minimum version
cmake_minimum_required(VERSION 3.8)

# Project name (target)
project(CLikeECS)

# CMake: output directories
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Standard modules directories
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")

# Project directories
include_directories(bin/)
include_directories(src/)
include_directories(include/)
include_directories(lib/)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

## SDL2_image
#find_package(SDL2_image REQUIRED)
#include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
#
## SDL2_ttf
#find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_TTF_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

## GoogleTest & GoogleMock (Unit Testing)
#add_subdirectory(lib/googletest-master)
#include_directories(lib/googletest-master/googletest/include)
#include_directories(lib/googletest-master/googlemock/include)

# Source files (to compile)
set(SOURCE_FILES
        include/entities/Entity.h
        include/utils/DebugNameComponentManager.h
        include/managers/EntityManager.h
        include/managers/InstanceData.h
        include/components/Vector3.h
        include/managers/Manager.h
        include/components/Vector2.h
        include/managers/JSONHandler.h
        include/managers/InstanceSystem.h
        include/systems/System.h
        include/managers/InstanceSystem.h
        src/managers/JSONHandler.cpp
        src/managers/Manager.cpp
        src/managers/EntityManager.cpp
        src/utils/DebugNameComponentManager.cpp
        src/systems/System.cpp
        src/main.cpp
        include/entities/Mask.h
        include/managers/SystemManager.h
        src/managers/SystemManager.cpp
        include/systems/Physics2D.h
        src/systems/Physics2D.cpp
        include/systems/DefaultSystem.h
        src/systems/DefaultSystem.cpp
        include/components/Sprite.h
        include/systems/Renderer2D.h
        include/components/Transform.h
        src/systems/Renderer2D.cpp
        include/components/Transform.h
        src/components/Vector3.cpp
        include/utils/MaskMapper.h
        src/utils/MaskMapper.cpp
        src/display/Screen.cpp
        include/display/Screen.h
        include/scenes/SceneOpenGL.h
        include/effects/Shader.h
        src/scenes/SceneOpenGL.cpp
        src/effects/Shader.cpp include/components/Matrix4x4.h)

# Executable
add_executable(CLikeECS ${SOURCE_FILES})

# Link libraries
target_link_libraries(CLikeECS ${OPENGL_LIBRARIES})
target_link_libraries(CLikeECS ${SDL2_LIBRARIES})
#target_link_libraries(CLikeECS ${SDL2_IMAGE_LIBRARIES})
#target_link_libraries(CLikeECS ${SDL2_TTF_LIBRARIES})
#target_link_libraries(CLikeECS gtest gtest_main)