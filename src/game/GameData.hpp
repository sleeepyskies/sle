#pragma once
#include "../graphics/Window.hpp"
#include "../map/TileMap.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include <SDL.h>
#include <unordered_map>
#include <vector>

namespace sle {
class GameData {
public:
    void loadMap(const TileMapResult &tmRes);

    void update(const std::unordered_map<SDL_Keycode, bool> &keys, const glm::ivec2 &mousePos);

    void draw(const ref<Window> &ren) const;

private:
    Camera m_camera;
    TileMap m_map;
};

} // namespace sle
