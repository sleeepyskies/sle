cmake_minimum_required(VERSION 3.15...3.31)
project(sle) # set project name

set(CMAKE_CXX_STANDARD 20)

# generate config.h
include(cmake/config.cmake)

# slog is my own lightweight header only logging library used throughout this project
include(FetchContent)
FetchContent_Declare(
        slog
        GIT_REPOSITORY https://github.com/sleeepyskies/slog.git
        GIT_TAG main
)
FetchContent_MakeAvailable(slog)

# get dependencies. I have installed these using vcpkg, and have configured
# clion to look at this install location
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)

# define an executable using the listed .cpp files. .cpp files will be turned into .o files and be linked together
# header files are not compiled but copy pasted or included into .cpp files before compilation, whereas source
# files turn into .o files. .o files are binary
add_executable(sle
        src/main.cpp
        src/Engine.cpp
        src/Engine.hpp
        src/Renderer.cpp
        src/Renderer.hpp
        src/GameData.cpp
        src/GameData.hpp
        src/EventHandler.cpp
        src/EventHandler.hpp
        src/Constants.hpp
        src/Entity.cpp
        src/Entity.hpp
        src/AssetManager.cpp
        src/AssetManager.hpp
        src/math.hpp
        src/Camera.cpp
        src/Camera.hpp
        src/MapSerializer.cpp
        src/MapSerializer.hpp
        src/TileMap.cpp
        src/TileMap.hpp
        src/Texture.hpp
        src/core.hpp
)

target_include_directories(sle PRIVATE ${slog_SOURCE_DIR})
target_link_libraries(sle PRIVATE SDL2::SDL2 SDL2_image::SDL2_image glm::glm)