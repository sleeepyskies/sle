#pragma once
#include <vector>
#include "Entity.hpp"
#include "Map.hpp"
#include "Renderer.hpp"

class GameData {
private:
    Map m_map{};
    std::vector<Entity> m_entities{};

public:
    void renderMap(Renderer &ren);
    void renderEntities(Renderer &ren);
};
