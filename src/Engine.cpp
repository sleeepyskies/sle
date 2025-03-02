#include "Engine.hpp"

namespace sle {
Engine::Engine(): m_renderer(), m_gameData(), m_eventHandler() {
    init();
    run();
}

void Engine::init() {
    nfo("Engine initialised successfully");
}

void Engine::run() {
    // still need to handle cycle length properly to get desired FPS, this has been
    // done for now with SDL_RENDERER_PRESENTVSYNC flag in the SDL_Renderer
    while (m_gameData.running()) {
        m_eventHandler.input(m_gameData);
        update();
        render();
    }
}

void Engine::update() {
    // still need to do updates on everything else in the game such as camera and entities
    m_gameData.updateRunning();
    m_gameData.updateCamera();
    m_gameData.updateMap();
    m_gameData.updateEntities();
}

void Engine::render() const {
    m_renderer.clear();
    m_gameData.drawMap(m_renderer);
    m_renderer.present();
}

} // namespace sle
