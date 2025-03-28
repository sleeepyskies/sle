#include "Window.hpp"

namespace sle {
Window::Window() {
    m_window = SDL_CreateWindow(
        WINDOW_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

    if (m_window == nullptr) {
        const auto err = SDL_GetError();
        SDL_Quit();
        IMG_Quit();
        throw std::runtime_error(err);
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (m_renderer == nullptr) {
        const auto err = SDL_GetError();
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        IMG_Quit();
        throw std::runtime_error(err);
    }

    nfo("Engine Window successfully initialised.");
}

Window::~Window() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    nfo("Engine Window has been destroyed.");
}

void Window::clear(const Color &color) const {
    if (SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a) != 0) {
        err("Could not set render draw color. {}", SDL_GetError());
    }
    if (SDL_RenderClear(m_renderer) != 0) {
        err("Could not clear the renderer. {}", SDL_GetError());
    }
}

void Window::present() const { SDL_RenderPresent(m_renderer); }

} // namespace sle
