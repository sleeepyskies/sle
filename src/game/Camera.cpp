#include "Camera.hpp"

namespace sle {

void Camera::move(const glm::ivec2 direction) {
    glm::vec2 normalized = normalize(glm::vec2{ direction });
    m_pos += glm::ivec2{ normalized * CAMERA_SPEED };
    trc("Camera now located at ({}. {})", m_pos.x, m_pos.y);
}

void Camera::update(const hashmap<SDL_Keycode, bool> &keysPressed) {
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