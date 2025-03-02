#include "Renderer.hpp"

namespace sle {
Renderer::Renderer() {
    // 0 on success
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    nfo("SDL initialised successfully");

    // 0 on failure
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG ) == 0 ) {
        SDL_Quit();
        throw std::runtime_error(IMG_GetError());
    }
    nfo("IMG initialised successfully");

    m_window = SDL_CreateWindow(
        WINDOW_NAME.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_RESIZABLE
        );

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

    nfo("Engine Renderer successfully initialised.");
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    IMG_Quit();

    nfo("Engine renderer has been destroyed.");
    nfo("Engine has shutdown.");
}

void Renderer::clear() const {
    if (SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) != 0) {
        err("Could not set render draw color. {}", SDL_GetError());
    }
    if (SDL_RenderClear(m_renderer) != 0) {
        err("Could not clear the renderer. {}", SDL_GetError());
    }
}

void Renderer::present() const {
    SDL_RenderPresent(m_renderer);
}



} // namespace sle
