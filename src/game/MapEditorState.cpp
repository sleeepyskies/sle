#include "MapEditorState.hpp"

namespace sle {

void MapEditorState::update(const InputData &inputData) {
    m_camera.update(inputData.keys);
    m_tileMap->findCursorTile(m_camera, inputData.mousePos);
}

void MapEditorState::draw() {
    m_window->clear();
    m_tileMap->draw(m_camera, m_window);
    m_window->present();
}

void MapEditorCamera::move(const glm::ivec2 direction) {
    glm::vec2 normalized = normalize(glm::vec2{ direction });
    m_pos += glm::ivec2{ normalized * CAMERA_SPEED };
    trc("MapEditorCamera now located at ({}. {})", m_pos.x, m_pos.y);
}

void MapEditorCamera::update(const std::unordered_map<SDL_Keycode, bool> &keysPressed) {
    glm::vec2 direction{};

    if (const auto it = keysPressed.find(SDLK_w); it != keysPressed.end() && it->second)
        direction.y += 1;
    if (const auto it = keysPressed.find(SDLK_a); it != keysPressed.end() && it->second)
        direction.x += 1;
    if (const auto it = keysPressed.find(SDLK_s); it != keysPressed.end() && it->second)
        direction.y -= 1;
    if (const auto it = keysPressed.find(SDLK_d); it != keysPressed.end() && it->second)
        direction.x -= 1;

    if (direction.x == 0 && direction.y == 0)
        return;

    move(direction);
}

} // namespace sle