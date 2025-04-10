#pragma once
#include <SDL_render.h>

#include "Window.hpp"
#include "slog.hpp"

namespace sle {
class Entity {
public:
    Entity(const unsigned int id, const SDL_Rect pos, SDL_Texture *texture)
        : m_id(id), m_pos(pos), m_texture(texture) {}

    void renderSelf(Window &ren) const;

private:
    const unsigned int m_id;
    SDL_Rect m_pos;
    SDL_Texture *m_texture;
};

} // namespace sle
