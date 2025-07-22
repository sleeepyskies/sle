cmake_minimum_required(VERSION 3.15...3.31)
project(sle)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# generate config.h
include(cmake/config.cmake)

# slog is my own lightweight header only logging library used throughout this
# project
include(FetchContent)
FetchContent_Declare(
	slog
	GIT_REPOSITORY https://github.com/sleeepyskies/slog.git
	GIT_TAG main)
FetchContent_MakeAvailable(slog)
# secs is my own ecs library
add_subdirectory(external/secs)

# get dependencies. I have installed these using vcpkg, and have configured
# clion to look at this install location (windows)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)

# define an executable using the listed .cpp files. .cpp files will be turned
# into .o files and be linked together header files are not compiled but copy
# pasted or included into .cpp files before compilation, whereas source files
# turn into .o files. .o files are binary
add_executable(
	sle
	src/main.cpp
	src/core/Engine.cpp
	src/core/Engine.hpp
	src/graphics/Window.cpp
	src/graphics/Window.hpp
	src/core/Input.cpp
	src/core/Input.hpp
	src/assets/AssetManager.cpp
	src/assets/AssetManager.hpp
	src/serialization/MapSerializer.cpp
	src/serialization/MapSerializer.hpp
	src/serialization/TileMap.cpp
	src/serialization/TileMap.hpp
	src/graphics/Texture.hpp
	# ecs
	# components
	src/ecs/components/CameraComponent.hpp
	src/ecs/components/TextureComponent.hpp
	src/ecs/components/TransformComponent.hpp
	# systems
	src/ecs/systems/CameraSystem.hpp
	src/ecs/systems/RenderSystem.hpp
	# util
	src/util/constants.hpp
	src/util/math.hpp
	src/util/types.hpp
	src/util/files.hpp
	src/util/assert.hpp
	src/core/MouseKey.hpp
	src/core/KeyboardKey.hpp
	src/graphics/Renderer.cpp
	src/graphics/Renderer.hpp
	src/serialization/TextSceneSerializer.cpp
	src/serialization/TextSceneSerializer.hpp
	src/serialization/ISceneSerializer.hpp)

target_include_directories(
	sle
	PRIVATE ${CMAKE_SOURCE_DIR}/src
			${CMAKE_SOURCE_DIR}/src/assets
			${CMAKE_SOURCE_DIR}/src/core
			${CMAKE_SOURCE_DIR}/src/ecs
			${CMAKE_SOURCE_DIR}/src/ecs/components
			${CMAKE_SOURCE_DIR}/src/ecs/systems
			${CMAKE_SOURCE_DIR}/src/game
			${CMAKE_SOURCE_DIR}/src/graphics
			${CMAKE_SOURCE_DIR}/src/map
			${CMAKE_SOURCE_DIR}/src/util
			${slog_SOURCE_DIR}
			external/secs)

target_link_libraries(sle PRIVATE SDL2::SDL2 SDL2_image::SDL2_image glm::glm)
