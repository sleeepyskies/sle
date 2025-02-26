#pragma once
#include <queue>
#include <SDL_events.h>
#include "slog.hpp"

#include "GameData.hpp"

namespace sle {
class EventHandler {
private:
    std::queue<std::pair<SDL_Event, SDL_EventType>> m_eventQueue{};

public:
    void enqueueEvent(SDL_Event &event, SDL_EventType eventType);
    void processEvents(GameData &gameData);
};

} // namespace sle
