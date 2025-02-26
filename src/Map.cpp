#include "Map.hpp"

#include "GameData.hpp"

namespace sle {
Map::Map() {
    m_tiles.resize(MAP_WIDTH);
}


void Map::renderTiles(Renderer &ren) const {
    for (const auto &row : m_tiles) {
        for (const auto &tile: row) {
            tile.renderSelf(ren);
        }
    }
}


void Map::updateTiles(const glm::ivec2 mousePos) {
    const glm::ivec2 overTile = toGrid(mousePos);

    if (overTile.x < 0 || overTile.y < 0 || overTile.x >= m_tiles.size() || overTile.y >= m_tiles[0].size()) return;
    if (m_selectedTile == overTile) return;

    // unselect the selected tile
    m_tiles[overTile.x][overTile.y].translate(UN_HIGHLIGHT_TILE);

    // highlight new tile
    m_selectedTile = overTile;
    m_tiles[overTile.x][overTile.y].translate(HIGHLIGHT_TILE);
}

void Map::addTile(SDL_Texture* texture) {
    for (int rowIndex = 0; rowIndex < MAP_WIDTH; rowIndex++) {
        if (m_tiles[rowIndex].size() >= MAP_HEIGHT) continue;

        const glm::ivec2 position = toIsometric(rowIndex, (m_tiles[rowIndex].size()));

        SDL_Rect pos{};
        pos.w = TILE_WIDTH;
        pos.h = TILE_HEIGHT;
        pos.x = position.x;
        pos.y = position.y;

        const Tile newTile{ pos, texture };

        m_tiles[rowIndex].push_back(newTile);
    }
}

} // namespace sle
