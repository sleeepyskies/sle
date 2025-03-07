#pragma once
#include "math.hpp"
#include "slog.hpp"
#include <SDL_events.h>
#include <queue>

#include "GameData.hpp"

namespace sle {
class EventHandler {
private:
    /// @brief The current mouse position in screen coordinates.
    glm::ivec2 m_mousePos;
    /// @brief A map of all keys, with information whether they are currently pressed.
    std::unordered_map<SDL_Keycode, bool> m_keys;

    void handleMouseMotion(const SDL_Event &event, GameData &gameData);

public:
    EventHandler(): m_mousePos(glm::ivec2{0, 0}) {}
    ~EventHandler() = default;

    void input(GameData &gameData);
};

} // namespace sle
