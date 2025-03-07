#include "EventHandler.hpp"

namespace sle {

EventHandler::EventHandler() : m_mousePos(glm::ivec2{ 0, 0 }) {
    for (auto [_, v] : m_keys)
        v = false;
}

bool EventHandler::pollEvents() {
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_QUIT:
            return false;
        case SDL_MOUSEMOTION:
            m_mousePos.x = m_event.motion.x;
            m_mousePos.y = m_event.motion.y;
            break;
        case SDL_KEYDOWN:
            // 0 if not a key repeat
            if (m_event.key.repeat == 0)
                m_keys[m_event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_keys[m_event.key.keysym.sym] = false;
            break;
        default:
            break;
        }
    }
    return !m_keys[SDLK_ESCAPE];
}

} // namespace sle
