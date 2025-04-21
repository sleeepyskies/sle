#pragma once
#include "constants.hpp"
#include <SDL.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/mat2x2.hpp>
#include <glm/vec2.hpp>

namespace sle {

// -------- Camera Offset ----------------

/**
 * @brief Offsets the given pos vector relative to the camera vector.
 * @param cam The camera position vector.
 * @param pos The position to offset as a 2D vector.
 * @returns An offset glm::ivec2.
 */
inline glm::ivec2 makeOffsetVec(const glm::ivec2 cam, const glm::ivec2 pos) {
    return pos - cam;
}

/**
 * @brief Offsets the given pos vector relative to the camera vector.
 * @param cam The camera position vector.
 * @param pos The position to offset as a 2D vector.
 * @returns An offset SDL_Rect.
 */
inline SDL_Rect makeOffsetRect(const glm::ivec2 cam, const glm::ivec2 pos) {
    const glm::ivec2 offs = pos - cam;
    return SDL_Rect{ offs.x, offs.y, 0, 0 };
}


// -------- Linear Algebra Math ----------------

/**
 * @brief This matrix transform goes from tile indices to screen coordinates. Can be used for
 * finding the position to render a sprite given its position in storage.
 */
constexpr glm::mat2 tileToScreenM{ TILE_WIDTH * 0.5f, 0.25f * TILE_HEIGHT, -TILE_WIDTH * 0.5f, 0.25f * TILE_HEIGHT };

/**
 * @brief This matrix transform goes from screen coordinates to the tile index. It however does not
 * include any shearing to account for the rotated tiles. For this, subtract half of the
 * TILE_HEIGHT from x before using.
 */
constexpr glm::mat2 screenToTileM{ 1.f / HALF_TILE_WIDTH / 2.f,
                                   1.f / -HALF_TILE_WIDTH / 2.f,
                                   1.f / QUARTER_TILE_HEIGHT / 2.f,
                                   1.f / QUARTER_TILE_HEIGHT / 2.f };

/**
 * @brief Takes a tiles indices in a 2D std::vector, and outputs its corresponding coordinates on the screen.
 */
inline glm::vec2 tileToScreen(const glm::ivec2 pos) { return { tileToScreenM * pos }; }

/**
 * @brief Takes a position on the screen, and outputs the tile indices that this position corresponds to.
 * @warning The function may output negative indices or out of bound indices. This is not checked here.
 */
inline glm::ivec2 screenToTile(const glm::ivec2 &pos) {
    return { screenToTileM * glm::vec2{ pos.x - HALF_TILE_HEIGHT, pos.y } };
}

/**
 * @brief Takes a tiles indices in a 2D std::vector, and outputs its corresponding coordinates on the screen.
 */
inline SDL_Rect tileToScreen(const SDL_Rect pos) {
    const glm::ivec2 posVec{ pos.x, pos.y };
    const glm::ivec2 resultVec = tileToScreenM * posVec;
    return { resultVec.x, resultVec.y, pos.w, pos.h };
}

/**
 * @brief Takes a position on the screen, and outputs the tile indices that this position corresponds to.
 * @warning The function may output negative indices or out of bound indices. This is not checked here.
 */
inline SDL_Rect screenToTile(const SDL_Rect &pos) {
    const glm::ivec2 posVec{ pos.x - HALF_TILE_HEIGHT, pos.y };
    const glm::ivec2 resultVec = screenToTileM * posVec;
    return { resultVec.x, resultVec.y, pos.w, pos.h };
}

} // namespace sle
