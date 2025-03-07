#pragma once
#include "Camera.hpp"
#include "Entity.hpp"
#include "Window.hpp"
#include "TileMap.hpp"
#include <SDL.h>
#include <unordered_map>
#include <vector>

namespace sle {
class GameData {
private:
    bool m_running = true;
    Camera m_camera;
    TileMap m_map;
    std::vector<Entity> m_entities{};
    glm::ivec2 m_mousePos{};
    std::unordered_map<SDL_Keycode, bool> m_keysPressed{};

    void updateRunning();

public:
    void loadMap(const TileMapResult &tmRes);
    void stop() { m_running = false; }
    bool running() const { return m_running; }

    void update();

    void draw(const ref<Window> &ren) const;

    void setMousePos(const int x, const int y) {
        m_mousePos.x = x;
        m_mousePos.y = y;
    };
    void keyDown(SDL_Keycode key);
    void keyUp(SDL_Keycode key);
};

} // namespace sle
