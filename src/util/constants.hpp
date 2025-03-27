#pragma once

#include <glm/vec2.hpp>
#include <string>

namespace sle {

const std::string WINDOW_NAME = "sle";
constexpr int WIDTH           = 1600;
constexpr int HEIGHT          = 850;

constexpr int TILE_HEIGHT           = 100;
constexpr int TILE_WIDTH            = 100;
constexpr float HALF_TILE_HEIGHT    = TILE_HEIGHT / 2.f;
constexpr float HALF_TILE_WIDTH     = TILE_WIDTH / 2.f;
constexpr float QUARTER_TILE_HEIGHT = TILE_HEIGHT / 4.f;
constexpr float QUARTER_TILE_WIDTH  = TILE_WIDTH / 4.f;

constexpr int CHUNK_SIZE = 16;
constexpr int CHUNK_TILE_COUNT = CHUNK_SIZE * CHUNK_SIZE;

constexpr glm::ivec2 HIGHLIGHT_TILE{ 0, -10 };
constexpr glm::ivec2 UN_HIGHLIGHT_TILE{ 0, 10 };

constexpr float CAMERA_SPEED = 5.f;

const std::string DEFAULT_MAP = "default";

} // namespace sle
