#pragma once

#include "Constants.hpp"
#include <string>
#include <glm/vec2.hpp>

namespace sle {
constexpr std::string WINDOW_NAME = "Window";
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 850;

constexpr int TILE_HEIGHT = 150;
constexpr int TILE_WIDTH = 150;

constexpr int MAP_HEIGHT = 10;
constexpr int MAP_WIDTH = 10;

constexpr glm::ivec2 HIGHLIGHT_TILE{0, -10};
constexpr glm::ivec2 UN_HIGHLIGHT_TILE{0, 10};

constexpr float CAMERA_SPEED = 10.f;


} // namespace sle
