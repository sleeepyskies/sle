#include "EventHandler.hpp"

namespace sle {

EventHandler::EventHandler() {
    for (auto [_, v] : m_inputData.keys)
        v = false;
}

void EventHandler::pollEvents() {
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_QUIT:
            m_engineData.quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_inputData.mouseClicks[m_event.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_inputData.mouseClicks[m_event.button.button] = false;
            break;
        case SDL_MOUSEMOTION:
            m_inputData.mousePos.x = m_event.motion.x;
            m_inputData.mousePos.y = m_event.motion.y;
            break;
        case SDL_KEYDOWN:
            // 0 if not a key repeat
            if (m_event.key.repeat == 0)
                m_inputData.keys[m_event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_inputData.keys[m_event.key.keysym.sym] = false;
            break;
        default:
            break;
        }
    }
}

} // namespace sle
