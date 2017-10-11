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
        include/Entity.h
        include/DebugNameComponentManager.h
        include/EntityManager.h
        include/InstanceData.h
        include/Vector3.h
        include/Manager.h
        include/Vector2.h
        include/Instance.h
        include/JSONHandler.h
        include/InstanceSystem.h
        include/System.h
        include/InstanceSystem.h
        src/JSONHandler.cpp
        src/Manager.cpp
        src/EntityManager.cpp
        src/DebugNameComponentManager.cpp
        src/System.cpp
        src/main.cpp include/Mask.h include/SystemManager.h)

# Executable
add_executable(CLikeECS ${SOURCE_FILES})

# Link libraries
#target_link_libraries(CLikeECS ${SDL2_LIBRARIES})
#target_link_libraries(CLikeECS ${SDL2_IMAGE_LIBRARIES})
#target_link_libraries(CLikeECS ${SDL2_TTF_LIBRARIES})