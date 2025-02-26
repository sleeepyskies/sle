#pragma once
#include <SDL_render.h>

#include "Renderer.hpp"
#include "slog.hpp"

namespace sle {
class Tile {
private:
    SDL_Rect m_pos;
    SDL_Texture *m_texture;

public:
    Tile(const SDL_Rect pos, SDL_Texture *texture): m_pos(pos), m_texture(texture) {}

    void renderSelf(const Renderer &ren) const;
    void translate(glm::ivec2 t);
};

} // namespace sle
