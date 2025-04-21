#pragma once

#include "AssetManager.hpp"
#include "Renderer.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "slog.hpp"
#include "secs/secs.hpp"
#include "SDL_timer.h"

namespace sle {

/**
 * @brief The Engine class serves as the glue for all systems in sle. The main application loop happens here,
 * and it controls the lifespan of the application.
 */
class Engine {

public:
    Engine() = default;

    ~Engine() = default;

    /// @brief Sets up the engine. Must be called before calling run().
    void init();

    /// @brief Shuts down the engine. Should only be called once the engine is no longer needed.
    void shutdown() const;

    /// @brief Starts the main application loop.
    void run();

private:
    /// @brief The scene object that contains the game.
    secs::Scene m_scene{};
    /// @brief The @ref AssetManager handles getting all loadable assets.
    ref<AssetManager> m_assetManager = nullptr;

    /// @brief Handles initialising SDL.
    void initSDL() const;
};

} // namespace sle