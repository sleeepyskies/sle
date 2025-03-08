#include "TileMap.hpp"

namespace sle {

const Tile *TileMap::tile(const int x, const int y) const {
    // find what chunk this coord lies in
    glm::i8vec2 chunkXY{ x / CHUNK_SIZE, y / CHUNK_SIZE };
    const auto chunk = m_chunks.find(chunkXY);
    if (chunk != m_chunks.end()) {
        return &(chunk->second.tile(x % CHUNK_SIZE, y % CHUNK_SIZE));
    }
    return nullptr;
}

Tile *TileMap::tile(const int x, const int y) {
    // find what chunk this coord lies in
    glm::i8vec2 chunkXY{ x / CHUNK_SIZE, y / CHUNK_SIZE };
    const auto chunk = m_chunks.find(chunkXY);
    if (chunk != m_chunks.end()) {
        return &(chunk->second.tile(x % CHUNK_SIZE, y % CHUNK_SIZE));
    }
    return nullptr;
}

void TileMap::load(const TileMapResult &tmRes) {
    m_chunks       = tmRes.chunks;
    m_tileTextures = tmRes.tileTextures;
    m_chunkIndices = tmRes.chunkIndices;
}

void TileMap::draw(const Camera &cam, const ref<Window> &ren) const {
    for (const auto cIndex : m_chunkIndices) {
        const auto &chunk = m_chunks.at(cIndex);

        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                const auto textureIndex = chunk.tile(x, y).textureIndex();
                if (textureIndex == 0xFF)
                    continue; // dead tile
                const glm::ivec2 screenPosition =
                    tileToScreen(glm::ivec2{ (cIndex.x * CHUNK_SIZE) + x, (cIndex.y * CHUNK_SIZE) + y });
                const SDL_Rect pos =
                    withCameraOffset(cam, SDL_Rect{ screenPosition.x, screenPosition.y, TILE_WIDTH, TILE_HEIGHT });

                auto textureDBG = m_tileTextures[textureIndex]->texture();

                if (SDL_RenderCopy(ren->renderer(), m_tileTextures[textureIndex]->texture(), nullptr, &pos) != 0) {
                    dbg("Could not render tile ({}, {}) in chunk ({}, {}). SDL_Error: {}",
                        x,
                        y,
                        cIndex.x,
                        cIndex.y,
                        SDL_GetError());
                }
            }
        }
    }
}

maybe<glm::i8vec2> TileMap::findCursorTile(const Camera &cam, const glm::ivec2 mousePos) {
    const glm::i8vec2 mouseTileIndex = screenToTile(withCameraOffset(cam, mousePos));
    /*
    const glm::i8vec2 mouseChunkIndex{ mouseTileIndex.x / CHUNK_SIZE, mouseTileIndex.y / CHUNK_SIZE };

    if (!m_chunks.contains(mouseChunkIndex))
        return {}; // cursor not over a chunk

    const int x = mouseTileIndex.x % CHUNK_SIZE;
    const int y = mouseChunkIndex.y % CHUNK_SIZE;
    if (m_chunks[mouseChunkIndex].tile(x, y).textureIndex() == 0xFF)
        return {}; // dead tile
        */

    return std::make_optional(mouseTileIndex);
}

} // namespace sle