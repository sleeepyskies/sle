#include "TileMap.hpp"

namespace sle {

// ReSharper disable once CppMemberFunctionMayBeStatic
bool TileMap::save() const { return MapSerializer::save(m_name, m_chunks, m_tileTextures); }

bool TileMap::load(const std::string &mapName) {
    if (const auto result = MapSerializer::load(mapName)) {
        m_name         = mapName;
        m_chunks       = result->chunks;
        m_tileTextures = result->tileTextures;
        m_chunkIndices = result->chunkIndices;
        return true;
    }
    return false;
}

void TileMap::draw(const Camera &cam, const Renderer &ren) const {
    for (const auto cIndex : m_chunkIndices) {
        const auto &chunk = m_chunks.at(cIndex);

        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                const auto textureIndex = chunk.tile(x, y).textureIndex();
                if (textureIndex == 0xFF)
                    continue; // dead tile
                const SDL_Rect pos = withCameraOffset(
                    cam, SDL_Rect{ (cIndex.x * CHUNK_SIZE) + x, (cIndex.y * CHUNK_SIZE) + y, TILE_WIDTH, TILE_HEIGHT });
                SDL_RenderCopy(ren.renderer(), m_tileTextures[textureIndex]->texture(), nullptr, &pos);
            }
        }
    }
}

std::optional<SDL_Rect> TileMap::findCursorTile(const Camera &cam, const glm::ivec2 mousePos) {
    const glm::ivec2 mouseTileIndex  = screenToTile(withCameraOffset(cam, mousePos));
    const glm::ivec2 mouseChunkIndex = mouseTileIndex / CHUNK_SIZE;

    // First check if the mouse is over a valid chunk. Perform binary search on sorted indices vector.
    if (!m_chunks.contains(mouseChunkIndex))
        return {}; // cursor not over a chunk

    const int x = mouseTileIndex.x % CHUNK_SIZE;
    const int y = mouseChunkIndex.y % CHUNK_SIZE;
    if (const Tile tile = m_chunks[mouseChunkIndex].tile(x, y); tile.textureIndex() == 0xFF)
        return {}; // dead tile

    return { SDL_Rect{ mouseChunkIndex.x + x, mouseChunkIndex.y + y, CHUNK_SIZE, CHUNK_SIZE } };
}

} // namespace sle
