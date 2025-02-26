#pragma once
#include <vector>
#include "Entity.hpp"
#include "Map.hpp"
#include "Renderer.hpp"

namespace sle {
class GameData {
private:
    Map m_map{};
    std::vector<Entity> m_entities{};
    glm::ivec2 m_mousePos{};

public:
    void renderMap(Renderer &ren);
    void renderEntities(Renderer &ren);
    void updateMap();
    void updateEntities();

    void addTile(SDL_Texture *texture);

    void setMousePos(const int x, const int y) { m_mousePos.x = x; m_mousePos.y = y; };
};

} // namespace sle
