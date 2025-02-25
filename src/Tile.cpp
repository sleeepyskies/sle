#include "Tile.hpp"

void Tile::renderSelf(const Renderer &ren) const {
    trc("Rendering Tile x:", m_pos.x, "y:", m_pos.y);
    SDL_RenderCopy(ren.getRenderer(), m_texture, nullptr, &m_pos);
}
