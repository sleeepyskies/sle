#include "GameData.hpp"

namespace sle {

void GameData::loadMap(const TileMapResult &tmRes) { m_map.load(tmRes); }

void GameData::draw(const ref<Renderer> &ren) const {
    m_map.draw(m_camera, ren);
    // draw entities
}

void GameData::update() {
    updateRunning();
    m_camera.update(m_keysPressed);
    m_map.findCursorTile(m_camera, m_mousePos);
    // update entities
}

void GameData::updateRunning() {
    const auto gotEsc = m_keysPressed.find(SDLK_ESCAPE);
    if (gotEsc != m_keysPressed.end() && m_keysPressed[SDLK_ESCAPE])
        m_running = false;
}

void GameData::keyDown(const SDL_Keycode key) {
    m_keysPressed[key] = true;
    dbg("Key {} pressed", key);
}

void GameData::keyUp(const SDL_Keycode key) {
    m_keysPressed[key] = false;
    dbg("Key {} released", key);
}

} // namespace sle
