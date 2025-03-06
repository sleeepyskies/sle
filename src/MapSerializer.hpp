#pragma once

#define GLM_ENABLE_EXPERIMENTAL // used for enabling hashing of glm::ivec2
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "config.h"
#include "core.hpp"
#include "utils.hpp"
#include <SDL.h>
#include <filesystem>
#include <fstream>
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace sle {

struct Chunk; // Forward declaration due to circular imports

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
 * uses a custom text format for storing map data. The format for the .map files used is as follows:
 * [Chunk location given as x y]
 * [blue | gray | green | red | empty] x CHUNK_SIZE * CHUNK_SIZE
 *
 *	This repeats for as many chunks as there are.
 */
class MapSerializer {
private:
    /// @brief Finds the index of the texture in the texture array. There may not exist one.
    std::optional<uint8_t> getIndex(const std::vector<ref<Texture>> &vec, const ref<Texture> &tex);

public:
    MapSerializer()  = default;
    ~MapSerializer() = default;

    /**
     * @brief Loads the map of the given name. Looks for this map in the default map location
     * specified in @ref Constants.hpp. Note that chunkIndices is required to be sorted for
     * rendering. This is done after all parsing has been done.
     */
    std::optional<TileMapResult> load(AssetManager &am, const std::string &mapName);

    /// @brief Saves the given map to disk at the default map location.
    bool save(const std::string &mapName, const std::unordered_map<glm::i8vec2, Chunk> &chunks,
                     const std::vector<ref<Texture>> &textures);
};

} // namespace sle
