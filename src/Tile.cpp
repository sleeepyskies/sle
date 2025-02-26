#include "Tile.hpp"

namespace sle {
void Tile::renderSelf(const Renderer &ren) const {
    const SDL_Rect renderPos = m_pos; // Copy updated position
    SDL_RenderCopy(ren.getRenderer(), m_texture, nullptr, &renderPos);
}


void Tile::translate(const glm::ivec2 t) {
    dbg("rect before, x: ", m_pos.x, ", y: ", m_pos.y);
    m_pos.x += t.x;
    m_pos.y += t.y;
    dbg("rect after, x: ", m_pos.x, ", y: ", m_pos.y);
}

} // namespace sle
