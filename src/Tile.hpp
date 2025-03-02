#pragma once
#include <SDL_render.h>

#include "Renderer.hpp"
#include "slog.hpp"
#include "Camera.hpp"

namespace sle {
class Tile {
private:
    SDL_Rect m_pos;
    SDL_Texture *m_texture;

public:
    Tile(const SDL_Rect pos, SDL_Texture *texture): m_pos(pos), m_texture(texture) {}

    void renderSelf(const Camera &cam, const Renderer &ren) const;
    void translate(glm::ivec2 t);

    SDL_Rect getPos() const { return m_pos; }
};

} // namespace sle
