#include "MapSerializer.hpp"
#include "TileMap.hpp"

namespace sle {

// TODO: Implement actual logic here!
std::optional<TileMapResult> MapSerializer::load(const std::string &mapName) {
    return {};
}

// TODO: Implement actual logic here!
bool MapSerializer::save(const std::string &mapName, const std::unordered_map<glm::i8vec2, Chunk> &chunks, const std::vector<SDL_Texture *> &textures) {
    return true;
}


} // sle