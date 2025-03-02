#pragma once

#include <array>
#include <string>
#include <vector>
#include "Map.hpp"
#include "Chunk.hpp"
#include "Tile.hpp"

namespace sle {

struct MapResult {
    std::unordered_map<glm::i8vec2, Chunk> chunks;
    std::vector<SDL_Texture*> textures;
    std::vector<glm::i8vec2> indices;
};

/// @brief This static class is used for loading map data from files and writing map data to files. sle
/// uses a custom binary format for storing map data. The format for the .map files used is as follows:
///
class MapSerializer {
public:
    MapSerializer() = delete;
    ~MapSerializer() = delete;

    /// @brief Loads the map of the given name. Looks for this map in the default map location.
    static std::optional<std::vector<Chunk>> load(const std::string &mapName);
    /// @brief Saves the given map to disk at the default map location.
    static bool save(
        const std::string &mapName,
        const std::unordered_map<glm::i8vec2, Chunk> &chunks,
        std::vector<SDL_Texture*> &textures
    );
};

} // sle
