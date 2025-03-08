#include "MapSerializer.hpp"
#include "TileMap.hpp"

namespace sle {
namespace fs = std::filesystem;

maybe<TileMapResult> MapSerializer::load(AssetManager &am, const std::string &mapName) {
    dbg("Loading map {}", mapName);
    const fs::path mapPath = fetchMapFile(mapName);

    std::ifstream inFile;
    inFile.open(mapPath);
    if (inFile.fail()) {
        err("Could not open file {}, unable to load map.", mapPath.string());
        return {};
    }

    std::unordered_map<glm::i8vec2, Chunk> chunks;
    std::vector<ref<Texture>> tileTextures;
    std::vector<glm::i8vec2> chunkIndices;

    while (inFile) {
        trc("Parsing new chunk!");

        Chunk chunk;
        glm::i8vec2 coords;
        if (auto result = readChunkCoords(inFile, chunkIndices))
            coords = *result;
        else
            break; // end of file, no new chunk left

        if (!readChunkTiles(inFile, chunk, tileTextures, am)) {
            err("Could not parse map {}", mapPath.generic_string());
            return {};
        }

        trc("Finished parsing chunk ({}, {})", coords.x, coords.y);

        chunks[coords] = chunk;
        chunkIndices.push_back(coords);
    }

    // make sure at least one chunk has been parsed.
    if (chunkIndices.size() < 1)
        return {};

    inFile.close();
    return std::make_optional(TileMapResult{ chunks, tileTextures, chunkIndices });
}

maybe<glm::i8vec2> MapSerializer::readChunkCoords(std::ifstream &inFile, const std::vector<glm::i8vec2> &chunkIndices) {
    int x, y;

    if (!(inFile >> x >> y))
        return {};

    if (x < INT8_MIN || x > INT8_MAX || y < INT8_MIN || y > INT8_MAX)
        return {};

    const glm::i8vec2 coord{ static_cast<int8_t>(x), static_cast<int8_t>(y) };
    for (const auto &c : chunkIndices) {
        if (c.x == coord.x && c.y == coord.y)
            return {};
    }

    return std::make_optional(coord);
}

bool MapSerializer::readChunkTiles(std::ifstream &inFile, Chunk &chunk, std::vector<ref<Texture>> &tileTextures,
                                   AssetManager &am) {
    for (int i = 0; i < CHUNK_TILE_COUNT; i++) {
        std::string tileIndicator;
        if (!(inFile >> tileIndicator))
            return false;

        if (!VALID_TILES.contains(tileIndicator + ".png"))
            return false;

        const std::filesystem::path texturePath = fetchTileTexture(tileIndicator);
        ref<Texture> texture                    = am.texture(texturePath);

        auto indexResult = getIndex(tileTextures, texture);
        Tile tile{ indexResult.value_or(tileTextures.size()) };
        if (!indexResult)
            tileTextures.push_back(texture);
        chunk.tile(i) = tile;
    }
    return true;
}

// TODO: Implement actual logic here!
bool MapSerializer::save(const std::string &mapName, const std::unordered_map<glm::i8vec2, Chunk> &chunks,
                         const std::vector<ref<Texture>> &textures) {
    return true;
}

maybe<uint8_t> MapSerializer::getIndex(const std::vector<ref<Texture>> &vec, const ref<Texture> &tex) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->texture() == tex->texture())
            return i;
    }
    return {};
}
} // namespace sle
