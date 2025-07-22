#include "Input.hpp"

namespace sle {

Input::Input() {
    for (auto [_, v] : m_keys)
        v = false;
}

Input &Input::get() {
    static Input instance;
    return instance;
}

void Input::poll() {
    auto e = SDL_Event();
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            m_active = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_mouseClicks[e.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_mouseClicks[e.button.button] = false;
            break;
        case SDL_MOUSEMOTION:
            m_mousePos.x = e.motion.x;
            m_mousePos.y = e.motion.y;
            break;
        case SDL_KEYDOWN:
            // 0 if not a key repeat
            if (e.key.repeat == 0) m_keys[e.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            m_keys[e.key.keysym.sym] = false;
            break;
        default:
            break;
        }
    }
}

bool Input::keyboardKey(const KeyboardKey key) const {
    const auto it = m_keys.find(key);
    return it != m_keys.end() && it->second;
}

bool Input::mouseKey(const MouseKey key) const { return m_mouseClicks[key]; }

glm::ivec2 Input::mousePos() const { return m_mousePos; }

bool Input::running() const { return m_active; }

} // namespace sle
