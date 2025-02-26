#include "GameData.hpp"

namespace sle {
void GameData::renderMap(Renderer &ren) {
    m_map.renderTiles(ren);
}

void GameData::renderEntities(Renderer &ren) {
    for (auto e : m_entities) {
        e.renderSelf(ren);
    }
}

void GameData::updateMap() {
    m_map.updateTiles(m_mousePos);
}

void GameData::updateEntities() {
    // TODO: add sumn here when i add entities

    return;
}

void GameData::addTile(SDL_Texture* texture) {
    trc("Adding tile to map");
    m_map.addTile(texture);
}
} // namespace sle
