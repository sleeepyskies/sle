#pragma once

#include "Constants.hpp"
#include <string>
#include <glm/vec2.hpp>

namespace sle {

constexpr std::string WINDOW_NAME = "sle";
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 850;

constexpr int TILE_HEIGHT = 150;
constexpr int TILE_WIDTH = 150;
constexpr float HALF_TILE_HEIGHT = TILE_HEIGHT / 2.f;
constexpr float HALF_TILE_WIDTH = TILE_WIDTH / 2.f;
constexpr float QUARTER_TILE_HEIGHT = TILE_HEIGHT / 4.f;
constexpr float QUARTER_TILE_WIDTH = TILE_WIDTH / 4.f;

constexpr int CHUNK_SIZE = 16;

constexpr glm::ivec2 HIGHLIGHT_TILE{0, -10};
constexpr glm::ivec2 UN_HIGHLIGHT_TILE{0, 10};

constexpr float CAMERA_SPEED = 10.f;

constexpr std::string_view DEFAULT_MAP = "default";
// TODO: use path objects for better path handling.
constexpr std::string_view MAP_FILE_PATH = "../assets/map-files";

} // namespace sle
