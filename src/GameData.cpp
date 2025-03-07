#include "GameData.hpp"

namespace sle {

void GameData::loadMap(const TileMapResult &tmRes) { m_map.load(tmRes); }

void GameData::draw(const ref<Window> &ren) const {
    m_map.draw(m_camera, ren);
    // draw entities
}

void GameData::update(const std::unordered_map<SDL_Keycode, bool> &keys, const glm::ivec2 &mousePos) {
    m_camera.update(keys);
    m_map.findCursorTile(m_camera, mousePos);
    // update entities
}

} // namespace sle
