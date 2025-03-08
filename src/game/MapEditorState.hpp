#pragma once

#include "GameStateMachine.hpp"
#include "TileMap.hpp"

namespace sle {

/**
 * @brief This camera is only for the @ref MapEditorState, and its movement and functionality
 * is hardcoded into sle.
 */
class MapEditorCamera {
public:
    glm::ivec2 getPos() const { return m_pos; }

    void update(const std::unordered_map<SDL_Keycode, bool> &keysPressed);

private:
    glm::ivec2 m_pos{ 0, 0 };

    void move(glm::ivec2 direction);
};

class MapEditorState : public IGameState {
public:
    MapEditorState(ref<Window> window, ref<TileMap> tileMap) : m_tileMap(tileMap), m_window(window) {}
    ~MapEditorState() = default;

    void update(const InputData &inputData) override;

    void draw() override;

    GameStateType toEnum() override { return GameStateType::MapEditor; }

private:
    /// @brief The active map.
    ref<TileMap> m_tileMap;
    ref<Window> m_window;

    /// @brief The map editor's camera. Its functionality is essentially hardcoded into the engine.
    Camera m_camera;
};

} // namespace sle
