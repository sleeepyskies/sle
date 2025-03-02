#pragma once

#include <unordered_map>
#include <algorithm>
#include "Constants.hpp"
#include "MapSerializer.hpp"
#include <glm/vec2.hpp>
#include <SDL.h>
#include "math.hpp"
#include "Renderer.hpp"

namespace sle {

/**
 * @brief A tile in sle for now is essentially just a uint8 type alias.
 *
 * However, it is kept as a struct in case future additions add extra attributes.
 * Note that no location is held here. This is because we can infer the tiles location
 * relative to its @ref Chunk via its index.
 */
struct Tile {
private:
    /// @brief The index into the texture array stored in @ref GameData. uint8 is used here,
    /// since this allows for up to 256 unique textures. Note that 0xFF is reserved for empty tiles.
    uint8_t m_textureIndex;

public:
    explicit Tile(const uint8_t textureIndex): m_textureIndex(textureIndex) {} // block type conversion

    uint8_t textureIndex() const { return m_textureIndex; } // getter
    uint8_t& textureIndex() { return m_textureIndex; } // setter
};

/**
 * @brief A chunk in sle holds a 16x16 grid of tiles (making a total of 256 tiles in a chunk).
 *
 * Note that std::vector is used here over std::array, since a full map will use around 16MB of
 * storage, which should not be stack allocated.
 */
struct Chunk {
    /// @brief The 16x16 grid of tiles that represent this chunk.
    std::vector<Tile> m_tiles;

    Chunk(): m_tiles(CHUNK_SIZE * CHUNK_SIZE) {} // allocate enough memory upon construction

    /// @brief Returns a non const reference to the tile at this index.
    Tile& tile (const int x, const int y) {
        const int index = y * CHUNK_SIZE + x;
        assert(index < CHUNK_SIZE * CHUNK_SIZE);
        return m_tiles[index];
    }

    /// @brief Returns a const reference to the tile at this index.
    const Tile& tile (const int x, const int y) const {
        const int index = y * CHUNK_SIZE + x;
        assert(index < CHUNK_SIZE * CHUNK_SIZE);
        return m_tiles[index];
    }
};

/**
 * @brief A map in sle is a mapping of Chunk location to chunk, as well as an array of all textures
 * used by tiles to avoid redundancy. Map is constructed without any map loaded.
 *
 * Note that a map can have up to 256x256 chunks. This class may not be fully necessary for now, as
 * it could be combined into GameData, but I have decided on giving it its own class in case of future
 * expansions to sle.
 */
class Map {
private:
    /// @brief The name of the map. Used for loading and saving.
    std::string m_name;
    /// @brief The chunks of tiles that the map consists of.
    std::unordered_map<glm::i8vec2, Chunk> m_chunks;
    /// @brief The textures used by tiles. Store this way to avoid redundant copies.
    std::vector<SDL_Texture*> m_tileTextures;
    /// @brief A sorted list of chunk indices. Order must be maintained when inserting.
    std::vector<glm::i8vec2> m_chunkIndices;

public:
    explicit Map(const std::string &mapName): m_name(mapName) {} // NOLINT(*-pass-by-value)
    ~Map();

    /// @brief Handles drawing the entire map to the window. Currently draws every chunk, even if not visible.
    void draw(const Camera &cam, const Renderer &ren) const;
    /// @brief Calculates and determines the location of the tile the cursor is over.
    std::optional<SDL_Rect> findCursorTile(const Camera &cam, glm::ivec2 mousePos);

    /// @brief Saves the current map to disk.
    bool save() const;
    /// @brief Loads either the provided map or the sle default map from disk.
    bool load(const std::string &mapName = DEFAULT_MAP);
};

} // sle
