#pragma once

#define GLM_ENABLE_EXPERIMENTAL // used for enabling hashing of glm::ivec2
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "config.h"
#include "types.hpp"
#include "util/files.hpp"
#include <SDL.h>
#include <filesystem>
#include <fstream>
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace sle {

struct Chunk; // Forward declaration due to circular imports
class TileMap;

/**
 * @brief Used to encapsulate the result of parsing a .slemap file.
 */
struct TileMapResult {
    std::unordered_map<glm::i8vec2, Chunk> chunks;
    std::vector<ref<Texture>> tileTextures;
    std::vector<glm::i8vec2> chunkIndices;
};

/**
 * @brief This static class is used for loading map data from files and writing map data to files. sle
 * uses a custom text format for storing map data. The format for the .map files can be found at:
 */
class MapSerializer {

public:
    MapSerializer()  = default;
    ~MapSerializer() = default;

    /**
     * @brief Loads the map of the given name. Looks for this map in the default map location
     * specified in @ref Constants.hpp. Note that chunkIndices is required to be sorted for
     * rendering. This is done after all parsing has been done.
     */
    maybe<TileMap> load(AssetManager &am, const std::string &mapName);

    /// @brief Saves the given map to disk at the default map location.
    bool save(const std::string &mapName, const std::unordered_map<glm::i8vec2, Chunk> &chunks,
              const std::vector<ref<Texture>> &textures);

private:
    /// @brief Finds the index of the texture in the texture array. There may not exist one.
    maybe<uint8_t> getIndex(const std::vector<ref<Texture>> &vec, const ref<Texture> &tex);
    /// @brief Reads and validates the chunks coords from the ifstream.
    maybe<glm::i8vec2> readChunkCoords(std::ifstream &inFile, const std::vector<glm::i8vec2> &chunkIndices);
    /// @brief Reads and validates all chunk tiles from the ifstream. Returns true if success.
    bool readChunkTiles(std::ifstream &inFile, Chunk &chunk, std::vector<ref<Texture>> &tileTextures, AssetManager &am);
};

} // namespace sle
