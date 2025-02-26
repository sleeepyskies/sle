#pragma once
#include <glm/vec2.hpp>
#include <glm/mat2x2.hpp>
#include "Constants.hpp"

namespace sle {
const glm::mat2 screenToIsometricTransform {

};

const glm::mat2 isometricToScreenTransform {

};

inline glm::ivec2 toIsometric(const int x, const int y) {
    return {
        (x * 0.5f * TILE_WIDTH) + (y * -0.5f * TILE_WIDTH) - (TILE_WIDTH / 2.f) + (WIDTH / 2.f),
        (x * 0.25f * TILE_HEIGHT) + (y * 0.25f * TILE_HEIGHT)
    };
}

inline glm::ivec2 toIsometric(const glm::ivec2 pos) {
    return {
        (pos.x * 0.5f * TILE_WIDTH) + (pos.y * -0.5f * TILE_WIDTH) - (TILE_WIDTH / 2.f) + (WIDTH / 2.f),
        (pos.x * 0.25f * TILE_HEIGHT) + (pos.y * 0.25f * TILE_HEIGHT)
    };
}

inline glm::vec2 toScreen(const int x, const int y) {

}

} // namespace sle
