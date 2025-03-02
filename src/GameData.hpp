#pragma once
#include <SDL_keyboard.h>
#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "Map.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

namespace sle {
class GameData {
private:
    bool m_running = true;
    Camera m_camera;
    Map m_map{};
    std::vector<Entity> m_entities{};
    glm::ivec2 m_mousePos{};
    std::unordered_map<SDL_Keycode, bool> m_keysPressed{};

public:
    void stop() { m_running = false; }
    bool running() const { return m_running; }

    void updateRunning();
    void updateCamera();
    void updateMap();
    void updateEntities();

    void renderMap(const Renderer &ren) const;
    void renderEntities(Renderer &ren) const;

    void addTile(SDL_Texture *texture);

    void setMousePos(const int x, const int y) { m_mousePos.x = x; m_mousePos.y = y; };
    void keyDown(SDL_Keycode key);
    void keyUp(SDL_Keycode key);
};

} // namespace sle
