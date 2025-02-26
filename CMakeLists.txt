cmake_minimum_required(VERSION 3.15...3.31)
project(SDL_Engine) # set project name

set(CMAKE_CXX_STANDARD 20)

# define an executable using the listed .cpp files. .cpp files will be turned into .o files and be linked together
# header files are not compiled but copy pasted or included into .cpp files before compilation, whereas source
# files turn into .o files. .o files are binary
add_executable(SDL_Engine
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
        src/Map.cpp
        src/Map.hpp
        src/Tile.cpp
        src/Tile.hpp
        src/AssetLoader.cpp
        src/AssetLoader.hpp
        src/math.hpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)
target_link_libraries(SDL_Engine PRIVATE SDL2::SDL2 SDL2_image::SDL2_image glm::glm)
