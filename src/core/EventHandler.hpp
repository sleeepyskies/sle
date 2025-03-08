#pragma once
#include "../../cmake-build-debug/_deps/slog-src/slog.hpp"
#include "../util/math.hpp"
#include <SDL_events.h>
#include <queue>

#include "GameData.hpp"

namespace sle {
/**
 * The EventManager is responsible for polling all SDL events
 */
class EventHandler {
public:
    EventHandler();
    ~EventHandler() = default;

    std::unordered_map<SDL_Keycode, bool> keys() { return m_keys; }

    glm::ivec2 mousePos() { return m_mousePos; }

    /**
     * @brief This reads in all SDL_Events and updates its state accordingly. Will return false
     * if the @ref Window should be closed and true otherwise.
     */
    bool pollEvents();

private:
    /// @brief The event used for polling events. Prevents creating a new event each tick.
    SDL_Event m_event;
    /// @brief The current mouse position in screen coordinates.
    glm::ivec2 m_mousePos;
    /// @brief A map of all keys, with information whether they are currently pressed.
    std::unordered_map<SDL_Keycode, bool> m_keys;
};

} // namespace sle
