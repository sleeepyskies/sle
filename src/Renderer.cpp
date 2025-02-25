#include "Renderer.hpp"

Renderer::Renderer() {
    m_window = SDL_CreateWindow(
        WINDOW_NAME.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_RESIZABLE
        );

    if (m_window == nullptr) {
        err("SDL window could not be created.");
        throw std::runtime_error(SDL_GetError());
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    if (m_renderer == nullptr) {
        err("SDL renderer could not be created.");
        throw std::runtime_error(SDL_GetError());
    }

    nfo("Engine Renderer successfully initialised.");
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    nfo("Engine renderer has been destroyed.");
}

void Renderer::clear() const {
    if (SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) != 0) {
        err("Could not set render draw color", SDL_GetError());
    }
    if (SDL_RenderClear(m_renderer) != 0) {
        err("Could not clear the renderer", SDL_GetError());
    }
}

void Renderer::present() const {
    SDL_RenderPresent(m_renderer);
}


