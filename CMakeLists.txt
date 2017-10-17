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
include_directories(bin)
include_directories(src)
include_directories(include)


## SDL2
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
#
## SDL2_image
#find_package(SDL2_image REQUIRED)
#include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
#
## SDL2_ttf
#find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_TTF_INCLUDE_DIRS})

set(SOURCE_FILES
        include/entities/Entity.h
        include/utils/DebugNameComponentManager.h
        include/managers/EntityManager.h
        include/managers/InstanceData.h
        include/components/Vector3.h
        include/managers/Manager.h
        include/components/Vector2.h
        include/utils/JSONHandler.h
        include/managers/InstanceSystem.h
        include/systems/System.h
        include/managers/InstanceSystem.h
        src/JSONHandler.cpp
        src/Manager.cpp
        src/EntityManager.cpp
        src/DebugNameComponentManager.cpp
        src/System.cpp
        src/main.cpp
        include/entities/Mask.h
        include/managers/SystemManager.h
        src/SystemManager.cpp
        include/systems/Physics2D.h
        src/Physics2D.cpp
        include/systems/DefaultSystem.h
        src/DefaultSystem.cpp
        include/components/Sprite.h
        include/systems/Renderer2D.h
        include/components/Transform.h
        src/Renderer2D.cpp
        include/components/Transform.h
        src/Vector3.cpp
        include/utils/MaskMapper.h src/MaskMapper.cpp)

# Executable
add_executable(CLikeECS ${SOURCE_FILES})

# Link libraries
#target_link_libraries(CLikeECS ${SDL2_LIBRARIES})
#target_link_libraries(CLikeECS ${SDL2_IMAGE_LIBRARIES})
#target_link_libraries(CLikeECS ${SDL2_TTF_LIBRARIES})