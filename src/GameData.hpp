#pragma once
#include "Camera.hpp"
#include "Entity.hpp"
#include "TileMap.hpp"
#include "Window.hpp"
#include <SDL.h>
#include <unordered_map>
#include <vector>

namespace sle {
class GameData {
private:
    Camera m_camera;
    TileMap m_map;
    std::vector<Entity> m_entities{};

public:
    void loadMap(const TileMapResult &tmRes);

    void update(const std::unordered_map<SDL_Keycode, bool> &keys, const glm::ivec2 &mousePos);

    void draw(const ref<Window> &ren) const;
};

} // namespace sle
