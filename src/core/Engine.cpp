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

    m_window = std::make_shared<Window>();
    m_assetManager.init(m_window);

    if (const auto tmRes = m_mapSerializer.load(m_assetManager, DEFAULT_MAP)) {
        m_gameData.loadMap(*tmRes);
    } else {
        throw std::runtime_error("Could not load a map, exiting program.");
    }
}

void Engine::run() {
    // still need to handle cycle length properly to get desired FPS, this has been
    // done for now with SDL_RENDERER_PRESENTVSYNC flag in the SDL_Renderer
    bool running = true;
    while (running) {
        running = m_eventHandler.pollEvents();
        m_gameData.update(m_eventHandler.keys(), m_eventHandler.mousePos());
        draw();
    }
}

void Engine::draw() const {
    m_window->clear();
    m_gameData.draw(m_window);
    m_window->present();
}

void Engine::shutdown() {
    SDL_Quit();
    IMG_Quit();
    nfo("Engine has shutdown.");
}

} // namespace sle
