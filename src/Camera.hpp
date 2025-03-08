#pragma once

#include "Constants.hpp"
#include "slog.hpp"
#include <SDL_keycode.h>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <unordered_map>

namespace sle {

class Camera {
public:
    glm::ivec2 getPos() const { return m_pos; }

    void update(const std::unordered_map<SDL_Keycode, bool> &keysPressed);

private:
    glm::ivec2 m_pos{ 0, 0 };

    void move(glm::ivec2 direction);
};

} // namespace sle
