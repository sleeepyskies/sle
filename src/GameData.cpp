#include "GameData.hpp"

namespace sle {
void GameData::renderMap(const Renderer &ren) const {
    m_map.draw(m_camera, ren);
}

void GameData::renderEntities(Renderer &ren) const {
    for (auto e : m_entities) {
        e.renderSelf(ren);
    }
}

void GameData::updateCamera() {
    glm::vec2 direction{};

    const auto gotW = m_keysPressed.find(SDLK_w);
    const auto gotA = m_keysPressed.find(SDLK_a);
    const auto gotS = m_keysPressed.find(SDLK_s);
    const auto gotD = m_keysPressed.find(SDLK_d);

    if (gotW != m_keysPressed.end() && m_keysPressed[SDLK_w]) direction.y += 1;
    if (gotA != m_keysPressed.end() && m_keysPressed[SDLK_a]) direction.x += 1;
    if (gotS != m_keysPressed.end() && m_keysPressed[SDLK_s]) direction.y -= 1;
    if (gotD != m_keysPressed.end() && m_keysPressed[SDLK_d]) direction.x -= 1;

    if (direction.x == 0 && direction.y == 0) return;

    m_camera.move(direction);
}

void GameData::updateRunning() {
    const auto gotEsc = m_keysPressed.find(SDLK_ESCAPE);
    if (gotEsc != m_keysPressed.end() && m_keysPressed[SDLK_ESCAPE]) m_running = false;
}

void GameData::updateMap() {
    m_map.updateTiles(m_camera, m_mousePos);
}

void GameData::updateEntities() {
    // TODO: add sumn here when i add entities
    return;
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
