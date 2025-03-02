#pragma once

#include <SDL_keycode.h>
#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include "Constants.hpp"
#include "slog.hpp"

namespace sle {

class Camera {
private:
    glm::ivec2 m_pos{0, 0};

    void move(glm::ivec2 direction);
public:
    glm::ivec2 getPos() const { return m_pos; }

    void update(const std::unordered_map<SDL_Keycode, bool> &keysPressed);
};

} // namespace sle
