#include "Tile.hpp"

namespace sle {
void Tile::renderSelf(const Renderer &ren) const {
    SDL_RenderCopy(ren.getRenderer(), m_texture, nullptr, &m_pos);
}

} // namespace sle
