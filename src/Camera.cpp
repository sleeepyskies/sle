#include "Camera.hpp"

namespace sle {

void Camera::move(const glm::ivec2 direction) {
    glm::vec2 normalized = normalize(glm::vec2{ direction });
    m_pos += glm::ivec2{ normalized * CAMERA_SPEED };
    trc("Moving camera in direction x: {} y: {}", normalized.x, normalized.y);
}


} // namespace sle