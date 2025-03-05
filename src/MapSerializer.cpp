#include "MapSerializer.hpp"

#include <bits/fs_path.h>

#include "TileMap.hpp"

namespace sle {

std::optional<TileMapResult> MapSerializer::load(const std::string &mapName) {
    // TODO add helper functions for easily getting files from certain dirs.
    const std::filesystem::path assetDir = ASSETS_PATH;
    const std::filesystem::path filePath = assetDir / "map-files" / (mapName + ".slemap");

    std::ifstream inFile;
    inFile.open(filePath);
    if (inFile.fail()) {
        err("Could not open file {}, unable to load map.", filePath);
        return {};
    }

    constexpr int tileAmount = CHUNK_SIZE * CHUNK_SIZE;

    std::unordered_map<glm::i8vec2, Chunk> chunks;
    std::vector<ref<Texture>> tileTextures;
    std::vector<glm::i8vec2> chunkIndices;

    while (!inFile.eof()) {
        Chunk chunk;
        glm::i8vec2 coords; // chunk coords in terms of chunks, not tiles
        inFile >> coords.x;
        inFile >> coords.y;
        for (int i = 0; i < tileAmount; i++) {
            std::string type;
            inFile >> type;
            Tile tile{ typeToTexture(type) };
            chunk.m_tiles[i] = tile;
        }

    }

    inFile.close();
    return { TileMapResult{ chunks, tileTextures, chunkIndices } };
}

// TODO: Implement actual logic here!
bool MapSerializer::save(const std::string &mapName, const std::unordered_map<glm::i8vec2, Chunk> &chunks, const std::vector<ref<Texture>> &textures) {
    return true;
}


} // sle