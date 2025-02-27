#pragma once

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include "Constants.hpp"
#include "slog.hpp"

namespace sle {

class Camera {
private:
    glm::ivec2 m_pos{0, 0};

public:
    glm::vec2 getPos() const { return m_pos; }

    void move(glm::vec2 direction);

};

} // namespace sle
