#include "GameData.hpp"

void GameData::renderMap(Renderer &ren) {
    m_map.render(ren);
}

void GameData::renderEntities(Renderer &ren) {
    for (auto e : m_entities) {
        e.render();
    }
}