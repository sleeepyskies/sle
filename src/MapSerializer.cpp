#include "MapSerializer.hpp"
#include "TileMap.hpp"

namespace sle {
namespace fs = std::filesystem;

std::optional<TileMapResult> MapSerializer::load(AssetManager &am, const std::string &mapName) {
    const fs::path mapPath = fetchMapFile(mapName);

    std::ifstream inFile;
    inFile.open(mapPath);
    if (inFile.fail()) {
        err("Could not open file {}, unable to load map.", mapPath.string());
        return {};
    }

    constexpr int tileAmount = CHUNK_SIZE * CHUNK_SIZE;

    std::unordered_map<glm::i8vec2, Chunk> chunks;
    std::vector<ref<Texture>> tileTextures;
    std::vector<glm::i8vec2> chunkIndices;

    // TODO GET BETTER LOOP PARSING LOGIC!!!
    dbg("PARSING NEW CHUNK!");
    Chunk chunk;
    glm::i8vec2 coords; // chunk coords in terms of chunks, not tiles
    int x, y;
    if (!(inFile >> x >> y)) {
        err("Could not parse map {}", mapPath.generic_string());
        throw std::runtime_error("Map Parsing Fail");
    }
    coords.x = static_cast<uint8_t>(x);
    coords.y = static_cast<uint8_t>(y);

    for (int i = 0; i < tileAmount; i++) {
        std::string tileIndicator;
        if (!(inFile >> tileIndicator)) {
            err("Could not parse map {}", mapPath.generic_string());
            throw std::runtime_error("Map Parsing Fail");
        }
        const std::filesystem::path texturePath = fetchTileTexture(tileIndicator);
        ref<Texture> texture                    = am.texture(texturePath);
        auto indexResult                        = getIndex(tileTextures, texture);
        Tile tile{ indexResult.value_or(tileTextures.size()) };
        if (!indexResult)
            tileTextures.push_back(texture);
        chunk.tile(i) = tile;
    }

    dbg("FINSIHED PARSING CHUNK");

    chunks[coords] = chunk;
    chunkIndices.push_back(coords);

    inFile.close();
    return { TileMapResult{ chunks, tileTextures, chunkIndices } };
}

// TODO: Implement actual logic here!
bool MapSerializer::save(const std::string &mapName, const std::unordered_map<glm::i8vec2, Chunk> &chunks,
                         const std::vector<ref<Texture>> &textures) {
    return true;
}

std::optional<uint8_t> MapSerializer::getIndex(const std::vector<ref<Texture>> &vec, const ref<Texture> &tex) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i]->texture() == tex->texture())
            return i;
    }
    return {};
}
} // namespace sle
