#include "GameData.hpp"

void GameData::renderMap(Renderer &ren) {
    m_map.renderTiles(ren);
}

void GameData::renderEntities(Renderer &ren) {
    for (auto e : m_entities) {
        e.renderSelf(ren);
    }
}

void GameData::addTile(SDL_Texture* texture) {
    trc("Adding tile to map");
    m_map.addTile(texture);
}