#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "Renderer.hpp"
#include "Tile.hpp"
#include "Constants.hpp"
#include <glm/vec2.hpp>
#include "math.hpp"

namespace sle {
class Map {
private:
    std::vector<std::vector<Tile>> m_tiles{};
    std::optional<glm::ivec2> m_selectedTile{};
public:
    Map();

    void renderTiles(Renderer &ren) const;
    void updateTiles(glm::ivec2 mousePos);
    void addTile(SDL_Texture *texture);
};

} // namespace sle
