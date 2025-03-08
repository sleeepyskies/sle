#include "PlayState.hpp"

namespace sle {

void PlayState::loadMap(const TileMapResult &tmRes) { m_map.load(tmRes); }

void PlayState::draw(const ref<Window> &ren) const { m_map.draw(m_camera, ren); }

void PlayState::update(const InputData &inputData) {
    m_camera.update(inputData.keys);
    m_map.findCursorTile(m_camera, inputData.mousePos);
}

} // namespace sle
