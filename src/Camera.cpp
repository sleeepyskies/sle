#include "Camera.hpp"

namespace sle {

void Camera::move(const glm::vec2 direction) {
    glm::vec2 normalized = glm::normalize(direction);
    m_pos += normalized * CAMERA_SPEED;
    trc("Moving camera in direction x: {} y: {}", normalized.x, normalized.y);
}


} // namespace sle