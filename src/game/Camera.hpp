#pragma once

#include "constants.hpp"
#include "slog.hpp"
#include "types.hpp"
#include <SDL_keycode.h>
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

namespace sle {

class Camera {
public:
    glm::ivec2 getPos() const { return m_pos; }

    void update(const hashmap<SDL_Keycode, bool> &keysPressed);

private:
    glm::ivec2 m_pos{ 0, 0 };

    void move(glm::ivec2 direction);
};

} // namespace sle
