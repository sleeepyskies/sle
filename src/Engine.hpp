#pragma once

#include "AssetManager.hpp"
#include "EventHandler.hpp"
#include "GameData.hpp"
#include "Renderer.hpp"
#include "slog.hpp"

namespace sle {

/**
 * @brief The Engine class serves as the glue for all systems in sle. The main application loop happens here,
 * and it controls the lifespan of the application.
 */
class Engine {
private:
    /// @brief The @ref Window acts as a wrapper for SDL_Window and SDL_Renderer, but serves more as a window in sle.
    Renderer m_renderer;
    /// @brief The @ref GameContext holds all of the games state.
    GameData m_gameData;
    /// @brief The @ref InputManager handles getting all user input and window events.
    EventHandler m_eventHandler;
    /// @brief The @ref AssetManager handles getting all loadable assets.
    AssetManager m_assetManager;
    /// @brief The @ref MapSerializer handles loading and saving maps from disk.
    MapSerializer m_mapSerializer;

public:
    Engine()  = default;
    ~Engine() = default;

    /// @brief Sets up the engine. Must be called before calling run().
    void init();
    /// @brief Shuts down the engine. Should only be called once the engine is no longer needed.
    void shutdown();

    /// @brief Starts the main application loop.
    void run();
};

} // namespace sle
