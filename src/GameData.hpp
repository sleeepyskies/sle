#pragma once
#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "TileMap.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include <SDL.h>

namespace sle {
class GameData {
private:
    bool m_running = true;
    Camera m_camera;
    TileMap m_map;
    std::vector<Entity> m_entities {};
    glm::ivec2 m_mousePos {};
    std::unordered_map<SDL_Keycode, bool> m_keysPressed {};

    void updateRunning();

public:
    void init();
    void stop() { m_running = false; }
    bool running() const { return m_running; }

    void update();

    void draw(const Renderer &ren) const;

    void setMousePos(const int x, const int y) { m_mousePos.x = x; m_mousePos.y = y; };
    void keyDown(SDL_Keycode key);
    void keyUp(SDL_Keycode key);
};

} // namespace sle
