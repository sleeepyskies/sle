#include "MapEditorState.hpp"

namespace sle {

MapEditorState::MapEditorState(ref<Window> window, ref<TileMap> tileMap, ref<AssetManager> &am)
    : m_tileMap(tileMap), m_window(window), m_assetManager(am) {
    m_tileToDraw        = am->texture("blue", MAP_TEXTURES_PATH);
    m_activeTileTexture = am->texture("selected-tile", MAP_TEXTURES_PATH);
}

void MapEditorState::update(const InputData &inputData) {
    m_camera.update(inputData.keys);
    m_activeTile = m_tileMap->findCursorTile(m_camera, inputData.mousePos);
    setTileToDraw(inputData.keys);
    performMouseEdit(inputData.mouseClicks);
}

void MapEditorState::draw() {
    m_window->clear();
    m_tileMap->draw(m_camera, m_window);
    drawActiveTile();
    m_window->present();
}

void MapEditorState::drawActiveTile() {
    if (m_activeTile && m_tileMap->tile(m_activeTile->x, m_activeTile->y)) {
        SDL_Rect pos =
            withCameraOffset(m_camera, tileToScreen({ m_activeTile->x, m_activeTile->y, TILE_WIDTH, TILE_HEIGHT }));
        SDL_RenderCopy(m_window->renderer(), m_activeTileTexture->texture(), nullptr, &pos);
    }
}

void MapEditorState::setTileToDraw(const std::unordered_map<SDL_Keycode, bool> &keysPressed) {
    if (const auto it = keysPressed.find(SDLK_1); it != keysPressed.end() && it->second) // 1 = blue
        m_tileToDraw = m_assetManager->texture("blue", MAP_TEXTURES_PATH);
    if (const auto it = keysPressed.find(SDLK_2); it != keysPressed.end() && it->second) // 2 = green
        m_tileToDraw = m_assetManager->texture("green", MAP_TEXTURES_PATH);
    if (const auto it = keysPressed.find(SDLK_3); it != keysPressed.end() && it->second) // 3 = gray
        m_tileToDraw = m_assetManager->texture("gray", MAP_TEXTURES_PATH);
    if (const auto it = keysPressed.find(SDLK_4); it != keysPressed.end() && it->second) // 4 = red
        m_tileToDraw = m_assetManager->texture("red", MAP_TEXTURES_PATH);
}

void MapEditorState::performMouseEdit(const std::array<bool, 5> &mouseButtons) {
    if (mouseButtons[1])
        addTile()
}


void MapEditorCamera::move(const glm::ivec2 direction) {
    glm::vec2 normalized = normalize(glm::vec2{ direction });
    m_pos += glm::ivec2{ normalized * CAMERA_SPEED };
    trc("MapEditorCamera now located at ({}. {})", m_pos.x, m_pos.y);
}

void MapEditorCamera::update(const std::unordered_map<SDL_Keycode, bool> &keysPressed) {
    glm::vec2 direction{};

    if (const auto it = keysPressed.find(SDLK_w); it != keysPressed.end() && it->second)
        direction.y += 1;
    if (const auto it = keysPressed.find(SDLK_a); it != keysPressed.end() && it->second)
        direction.x += 1;
    if (const auto it = keysPressed.find(SDLK_s); it != keysPressed.end() && it->second)
        direction.y -= 1;
    if (const auto it = keysPressed.find(SDLK_d); it != keysPressed.end() && it->second)
        direction.x -= 1;

    if (direction.x == 0 && direction.y == 0)
        return;

    move(direction);
}

} // namespace sle