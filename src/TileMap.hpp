#pragma once

#include "Constants.hpp"
#include "MapSerializer.hpp"
#include "Renderer.hpp"
#include "math.hpp"
#include <SDL.h>
#include <algorithm>
#include <vector>
#include <glm/vec2.hpp>
#include <unordered_map>
#include "AssetManager.hpp"

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
    /// @brief Defaults to empty/invalid tile texture index indicator if no argument is given.
    explicit Tile(const uint8_t textureIndex = 0xFF) : m_textureIndex(textureIndex) {} // block type conversion

    uint8_t textureIndex() const { return m_textureIndex; } // getter
    uint8_t &textureIndex() { return m_textureIndex; }      // setter
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

    Chunk() : m_tiles(CHUNK_SIZE * CHUNK_SIZE) {} // allocate enough memory upon construction

    /// @brief Returns a non const reference to the tile at this index.
    Tile &tile(const int x, const int y) {
        const int index = y * CHUNK_SIZE + x;
        assert(index < CHUNK_SIZE * CHUNK_SIZE);
        return m_tiles[index];
    }

    /// @brief Returns a const reference to the tile at this index.
    const Tile &tile(const int x, const int y) const {
        const int index = y * CHUNK_SIZE + x;
        assert(index < CHUNK_SIZE * CHUNK_SIZE);
        return m_tiles[index];
    }

    /// @brief Returns a non const reference to the tile at this index.
    Tile &tile(const int i) {
        assert(i < CHUNK_SIZE * CHUNK_SIZE);
        return m_tiles[i];
    }

    /// @brief Returns a const reference to the tile at this index.
    const Tile &tile(const int i) const {
        assert(i < CHUNK_SIZE * CHUNK_SIZE);
        return m_tiles[i];
    }
};

/**
 * @brief A tile map in sle is a mapping of Chunk location to chunk, as well as an array of all textures
 * used by tiles to avoid redundancy. Map is constructed without any map loaded.
 *
 * Note that a map can have up to 256x256 chunks. This class may not be fully necessary for now, as
 * it could be combined into GameData, but I have decided on giving it its own class in case of future
 * expansions to sle.
 */
class TileMap {
private:
    /// @brief The chunks of tiles that the map consists of.
    std::unordered_map<glm::i8vec2, Chunk> m_chunks;
    /// @brief The textures used by tiles. Store this way to avoid redundant copies.
    std::vector<ref<Texture>> m_tileTextures;
    /// @brief A sorted list of chunk indices. Order must be maintained when inserting.
    std::vector<glm::i8vec2> m_chunkIndices;

public:
    TileMap()  = default; // must call load() on TileMap after creating.
    ~TileMap() = default;

    /// @brief Handles drawing the entire map to the window. Currently draws every chunk, even if not visible.
    void draw(const Camera &cam, const ref<Renderer> &ren) const;
    /// @brief Calculates and determines the location of the tile the cursor is over.
    std::optional<SDL_Rect> findCursorTile(const Camera &cam, glm::ivec2 mousePos);

    /// @brief Sets this instances data using the given @ref TileMapResult struct.
    void load(const TileMapResult &tmRes);
};

} // namespace sle
