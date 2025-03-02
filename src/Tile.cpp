#include "Tile.hpp"

#include "math.hpp"

namespace sle {

void Tile::renderSelf(const Camera &cam, const Renderer &ren) const {
    const SDL_Rect offSet = withCameraOffset(cam, m_pos);
    SDL_RenderCopy(ren.getRenderer(), m_texture, nullptr, &offSet);
}

void Tile::translate(const glm::ivec2 t) {
    m_pos.x += t.x;
    m_pos.y += t.y;
}

} // namespace sle
