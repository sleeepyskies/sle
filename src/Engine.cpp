#include "Engine.hpp"

namespace sle {

void Engine::init() {
    // 0 on success
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    nfo("SDL initialised successfully");

    // 0 on failure
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        SDL_Quit();
        throw std::runtime_error(IMG_GetError());
    }
    nfo("IMG initialised successfully");

    m_renderer = std::make_shared<Renderer>();
    m_assetManager.init(m_renderer);

    nfo("Engine Renderer successfully initialised.");
}

void Engine::run() {
    // still need to handle cycle length properly to get desired FPS, this has been
    // done for now with SDL_RENDERER_PRESENTVSYNC flag in the SDL_Renderer
    while (m_gameData.running()) {
        m_eventHandler.input(m_gameData);
        m_gameData.update();
        draw();
    }
}

void Engine::draw() const {
    m_renderer->clear();
    const wref wRenderer = m_renderer;
    m_gameData.draw(wRenderer);
    m_renderer->present();
}

} // namespace sle
