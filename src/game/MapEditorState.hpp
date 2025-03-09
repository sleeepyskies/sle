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

    void update(const hashmap<SDL_Keycode, bool> &keysPressed);

private:
    glm::ivec2 m_pos{ 0, 0 };

    void move(glm::ivec2 direction);
};

/**
 * @brief This State represents the build in Isometric @ref TileMap editor. It makes use of a fixed
 * camera @ref MapEditorCamera, as well as allowing the user to save, edit and load maps.
 */
class MapEditorState : public IGameState {
public:
    MapEditorState(ref<Window> window, ref<TileMap> tileMap, ref<AssetManager> &am);
    ~MapEditorState() = default;

    void update(const InputData &inputData) override;

    void draw() override;

    GameStateType transition() { return m_nextState; }

    GameStateType toEnum() override { return GameStateType::MapEditor; }

private:
    /// @brief The active map.
    ref<TileMap> m_tileMap;
    ref<Window> m_window;

    /// @brief The @ref AssetManager to be able to create and destroy assets dynamically.
    ref<AssetManager> m_assetManager;

    /// @brief The map editor's camera. Its functionality is essentially hardcoded into the engine.
    Camera m_camera;

    /// @brief Used to handle state transitions.
    GameStateType m_nextState = GameStateType::MapEditor;

    /// @brief The tile that the mouse is over this tick.
    maybe<glm::i8vec2> m_activeTile{};
    /// @brief The texture used to render the active tile.
    ref<Texture> m_activeTileTexture = nullptr;
    /// @brief The tile that should be drawn to the screen.
    int m_tileToDraw = 0;

    /// @brief Draws a highlight around the active tile to the screen, if there is one.
    void drawActiveTile();

    /// @brief Picks the tile that will be placed, based on the users keyboard input.
    void setTileToDraw(const hashmap<SDL_Keycode, bool> &keys);

    /// @brief Edits the map if the user has pressed a mousse button.
    void performMouseEdit(const std::array<bool, 5> &mouseButtons);

    /**
     * @brief Adds the @ref m_tileToDraw to the mouse position. May create a new @ref Chunk
     * or overwrite an existing tile.
    */
    void addTile();
    /// @breif Removes the tile at the mouse position. May result in @ref Chunk deletion.
    void removeTile();
};

} // namespace sle
