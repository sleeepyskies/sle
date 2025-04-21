#pragma once

#include "KeyboardKey.hpp"
#include "MouseKey.hpp"
#include "math.hpp"
#include "slog.hpp"
#include "types.hpp"
#include <SDL_events.h>

namespace sle {

/**
 * @brief This struct is for any data that the @ref Engine may need to know.
 */
struct EngineData {
public:
    bool quit = false;
};

/**
 * @brief Input is a (almost) singleton that is used for querying user input. Due to the nature of
 * SDL, this must be a singleton and not a static utility class that forwards input calls to the
 * underlying api.
 *
 * Usage: @code Input::get().key(sdlKeycode) @endcode
 */
class Input {
public:
    /// Disable copy constructor
    Input(const Input &in) = delete;
    /// Disable copy assignment operator
    Input &operator=(const Input &in) = delete;

    /// @brief Returns the instance of Input.
    static Input& get();

    /**
     * @brief This reads in all SDL_Events and updates its state accordingly. Will return false
     * if the @ref Window should be closed and true otherwise.
     */
    void poll();

    /// @brief Returns true if the key is pressed.
    bool keyboardKey(KeyboardKey key) const;
    /// @brief Returns true if the mouse button is pressed.
    bool mouseKey(MouseKey key) const;
    /// @brief Returns the current mouse position.
    glm::ivec2 mousePos() const;
    /// @brief Returns true if no event has occurred to stop the engine.
    bool running() const;

private:
    /// Hide constructor
    Input();
    hashmap<KeyboardKey, bool> m_keys;
    glm::ivec2 m_mousePos{ 0, 0 };
    std::array<bool, 5> m_mouseClicks{}; // can be indexed using macro from SDL_mouse.h
    bool m_active = true;
};

} // namespace sle