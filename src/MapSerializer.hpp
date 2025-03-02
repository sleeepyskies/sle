#pragma once

#include <array>
#include <string>
#include <vector>
#include "Map.hpp"
#include "Chunk.hpp"
#include "Tile.hpp"

namespace sle {

/// @brief This static class is used for loading map data from files and writing map data to files. sle
/// uses a custom binary format for storing map data. The format for the .map files used is as follows:
///
class MapSerializer {
public:
    MapSerializer() = delete;
    ~MapSerializer() = delete;

    /// @brief Loads
    static std::vector<Chunk> load(const std::string &filePath);
    static void save(const std::string &filePath);
};

} // sle
