#include "EventHandler.hpp"

namespace sle {
void EventHandler::enqueueEvent(SDL_Event &event) {
    m_eventQueue.emplace(event);
}

void EventHandler::processEvents(GameData &gameData) {
    // ReSharper disable once CppJoinDeclarationAndAssignment
    SDL_Event event;

    while (!m_eventQueue.empty()) {
        event = m_eventQueue.front();

        switch (event.type) {
            case SDL_MOUSEMOTION:
                handleMouseMotion(event, gameData);
                break;
            default:
                break;
        }

        m_eventQueue.pop();
    }
}

void EventHandler::handleMouseMotion(const SDL_Event &event, GameData &gameData) {
    gameData.setMousePos(event.motion.x, event.motion.y);
    trc("Mouse is at position x: {}, y: {}", event.motion.x, event.motion.y);
}

} // namespace sle
