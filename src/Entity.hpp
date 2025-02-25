#pragma once
#include <SDL_render.h>

#include "Renderer.hpp"
#include "slog.hpp"

class Entity {
private:
    const unsigned int m_id;
    SDL_Rect m_pos;
    SDL_Texture *m_texture;

public:
    Entity(const unsigned int id, const SDL_Rect pos, SDL_Texture *texture): m_id(id), m_pos(pos),
        m_texture(texture) {
    }

    void renderSelf(Renderer &ren) const;
};
