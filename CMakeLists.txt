cmake_minimum_required(VERSION 3.29)
project(SDL_Engine)

set(CMAKE_CXX_STANDARD 20)

# add SDL2
set(SDL2_DIR ${PROJECT_SOURCE_DIR}/libs/SDL2)
set(SDL2_Image_DIR ${PROJECT_SOURCE_DIR}/libs/SDL2)

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
)

target_include_directories(SDL_Engine PRIVATE ${SDL2_DIR}/include/SDL2)

# link SDL2 and SDL_Image
if(WIN32)
    target_link_libraries(SDL_Engine
            ${SDL2_DIR}/lib/libSDL2.a
            ${SDL2_DIR}/lib/libSDL2main.a
            ${SDL2_Image_DIR}/lib/libSDL2_image.a
            setupapi
            imm32
            winmm
            version
    )
endif()