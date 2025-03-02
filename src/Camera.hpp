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
    glm::ivec2 getPos() const { return m_pos; }

    void move(glm::ivec2 direction);

};

} // namespace sle
