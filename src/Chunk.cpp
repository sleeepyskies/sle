#include "Chunk.hpp"

#include "GameData.hpp"

namespace sle {
Chunk::Chunk() {
    m_tiles.resize(CHUNK_SIZE);
}


void Chunk::renderTiles(const Camera &cam, const Renderer &ren) const {
    for (const auto &row : m_tiles) {
        for (const auto &tile: row) {
            tile.renderSelf(cam, ren);
        }
    }
}


void Chunk::updateTiles(const Camera &cam, const glm::ivec2 mousePos)  {
    const glm::ivec2 hoverTile = screenToTile(withCameraOffset(cam, mousePos)); // get the tile the mouse is over

    // Check if the mouse is over a tile, assumes a nxn tile map, TODO: change this for later adaptability
    if (hoverTile.x < 0 || hoverTile.y < 0 || hoverTile.x >= m_tiles.size() || hoverTile.y >= m_tiles[0].size()) {
        if (m_selectedTile) {
            m_tiles[m_selectedTile.value().x][m_selectedTile.value().y].translate(UN_HIGHLIGHT_TILE);
            m_selectedTile.reset();
        }
        return;
    };

    if (m_selectedTile && m_selectedTile.value() == hoverTile) return; // haven't moved from current tile

    // unselect the selected tile
    if (m_selectedTile) {
        m_tiles[m_selectedTile.value().x][m_selectedTile.value().y].translate(UN_HIGHLIGHT_TILE);
    }

    // highlight new tile
    m_selectedTile = hoverTile;
    m_tiles[m_selectedTile->x][m_selectedTile->y].translate(HIGHLIGHT_TILE);
}

void Chunk::addTile(SDL_Texture* texture) {
    for (int rowIndex = 0; rowIndex < CHUNK_SIZE; rowIndex++) {
        if (m_tiles[rowIndex].size() >= CHUNK_SIZE) continue;

        const glm::ivec2 position = tileToScreen({ rowIndex, (m_tiles[rowIndex].size()) });

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
