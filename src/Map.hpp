#pragma once

#include <vector>

#include "Renderer.hpp"
#include "Tile.hpp"
#include "Constants.hpp"
#include <glm/vec2.hpp>
#include "math.hpp"

namespace sle {
class Map {
private:
    std::vector<std::vector<Tile>> m_tiles{};
public:
    Map();

    void renderTiles(Renderer &ren);
    void addTile(SDL_Texture *texture);
};

} // namespace sle
