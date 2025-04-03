#pragma once

#include "AssetManager.hpp"
#include "EventHandler.hpp"
#include "GameStateMachine.hpp"
#include "MapEditorState.hpp"
#include "PlayState.hpp"
#include "graphics/Window.hpp"
#include "slog.hpp"

namespace sle {

/**
 * @brief The Engine class serves as the glue for all systems in sle. The main application loop happens here,
 * and it controls the lifespan of the application.
 */
class Engine {

public:
    Engine()  = default;
    ~Engine() = default;

    /// @brief Sets up the engine. Must be called before calling run().
    void init();
    /// @brief Shuts down the engine. Should only be called once the engine is no longer needed.
    void shutdown();
    /// @brief Starts the main application loop.
    void run();

private:
    /// @brief The @ref GameStateMachine manages switching between the engines current state.
    GameStateMachine m_state;
    /// @brief The @ref InputManager handles getting all user input and window events.
    EventHandler m_eventHandler;
    /// @brief The @ref AssetManager handles getting all loadable assets.
    ref<AssetManager> m_assetManager = nullptr;
    /// @brief The @ref MapSerializer handles loading and saving maps from disk.
    MapSerializer m_mapSerializer;

    /// @brief Handles initialising SDL.
    void initSDL();
};

} // namespace sle
