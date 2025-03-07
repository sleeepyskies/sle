#include "Entity.hpp"

namespace sle {
void Entity::renderSelf(Window &ren) const { trc("Rendering Entity {}", m_id); }

} // namespace sle
