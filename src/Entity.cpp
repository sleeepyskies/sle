#include "Entity.hpp"

namespace sle {
void Entity::renderSelf(Renderer &ren) const { trc("Rendering Entity {}", m_id); }

} // namespace sle
