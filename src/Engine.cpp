#include "Engine.hpp"

namespace sle {

Engine::Engine(): m_renderer(), m_gameData() {
    nfo("Engine successfully initialised.");
    run();
}

void Engine::run() {
    // still need to handle cycle length properly to get desired FPS, this has been
    // done for now with SDL_RENDERER_PRESENTVSYNC flag in the SDL_Renderer
    while (m_gameData.running()) {
        EventHandler::input(m_gameData);
        m_gameData.update();
        render();
    }
}

void Engine::render() const {
    m_renderer.clear();
    m_gameData.draw(m_renderer);
    m_renderer.present();
}

} // namespace sle
