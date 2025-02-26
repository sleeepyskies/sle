#pragma once
#include <queue>
#include <SDL_events.h>
#include "slog.hpp"
#include "math.hpp"

#include "GameData.hpp"

namespace sle {
class EventHandler {
private:
    std::queue<SDL_Event> m_eventQueue{};

    static void handleMouseMotion(const SDL_Event &event, GameData &gameData);

public:
    void enqueueEvent(SDL_Event &event);
    void processEvents(GameData &gameData);
};

} // namespace sle
