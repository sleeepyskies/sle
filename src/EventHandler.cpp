#include "EventHandler.hpp"

namespace sle {
void EventHandler::enqueueEvent(SDL_Event &event, SDL_EventType eventType) {
    m_eventQueue.emplace(event, eventType);
}

void EventHandler::processEvents(GameData &gameData) {
    std::pair<SDL_Event, ::SDL_EventType> eventData;

    while (!m_eventQueue.empty()) {
        eventData = m_eventQueue.front();
        // TODO: Do something with this event
        m_eventQueue.pop();
    }
}

} // namespace sle
