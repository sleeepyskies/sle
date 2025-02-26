#include "Map.hpp"

Map::Map() {
    m_tiles.resize(MAP_WIDTH);
}


void Map::renderTiles(Renderer &ren) {
    for (const auto &row : m_tiles) {
        for (const auto &tile: row) {
            tile.renderSelf(ren);
        }
    }
}

void Map::addTile(SDL_Texture* texture) {
    for (int rowIndex = 0; rowIndex < MAP_WIDTH; rowIndex++) {
        if (m_tiles[rowIndex].size() >= MAP_HEIGHT) continue;

        glm::ivec2 position = toIsometric(rowIndex, (m_tiles[rowIndex].size()));

        SDL_Rect pos{};
        pos.w = TILE_WIDTH;
        pos.h = TILE_HEIGHT;
        pos.x = position.x;
        pos.y = position.y;

        const Tile newTile{ pos, texture };

        m_tiles[rowIndex].push_back(newTile);
    }
}