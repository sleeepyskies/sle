#include "Map.hpp"

#include "MapSerializer.hpp"

namespace sle {

Map::~Map() {
    for (const auto texture: m_tileTextures)
        SDL_DestroyTexture(texture);
}

void Map::draw(const Camera &cam, const Renderer &ren) const {
    for (const auto cIndex : m_chunkIndices) {
        const auto chunk = m_chunks[cIndex];

        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                const auto texture = m_tileTextures[chunk.tile(x, y)];
                const SDL_Rect pos = withCameraOffset(
                    cam,
                    SDL_Rect{ cIndex.x + x, cIndex.y + y, TILE_WIDTH, TILE_HEIGHT }
                );
                SDL_RenderCopy(ren.getRenderer(), texture, nullptr, &pos);
            }
        }
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool Map::save() const {
    return MapSerializer::save(m_name, m_chunks, m_tileTextures);
}

bool Map::load(const std::string &mapName) {
    if (const auto success = MapSerializer::load(mapName)) {
        m_name = mapName;
        m_chunks = success.value().m_chunks;
        m_tileTextures = success.value().textures;
        m_chunkIndices = success.value().indices;
        return true;
    }
    return false;
}

} // sle