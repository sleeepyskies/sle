#pragma once
#include <glm/vec2.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "Constants.hpp"

namespace sle {
constexpr glm::mat3 gridToIsometricTransform {
    (0.5f * TILE_WIDTH), (0.25f * TILE_HEIGHT), 0.f,
    (-0.5f * TILE_HEIGHT), (0.25f * TILE_HEIGHT), 0.f,
    (WIDTH / 2.f) - (TILE_WIDTH / 2.f), 0.f, 1.f
};

const glm::mat2 inv = glm::inverse(glm::mat2{gridToIsometricTransform});
const glm::vec2 invTranslation = -(inv * glm::vec2{gridToIsometricTransform[2]});

const glm::mat3 isometricToGridTransform {
    inv[0][0], inv[0][1], 0.f,
    inv[1][0], inv[1][1], 0.f,
    invTranslation.x, invTranslation.y, 1.f
};

inline glm::vec2 toIsometric(const int x, const int y) {
    return gridToIsometricTransform * glm::vec3(x, y, 1.f);
}

inline glm::vec2 toIsometric(const glm::ivec2 pos) {
    return toIsometric(pos.x, pos.y);
}

inline glm::vec2 toGrid(const int x, const int y) {
    return isometricToGridTransform * glm::vec3(x, y, 1.f);
}

inline glm::vec2 toGrid(const glm::ivec2 pos) {
    return toGrid(pos.x, pos.y);
}

} // namespace sle
