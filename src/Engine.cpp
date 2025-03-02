#include "Engine.hpp"

namespace sle {
Engine::Engine(): m_renderer(), m_gameData(), m_eventHandler() {
    init();
    run();
}

void Engine::init() {
    const std::string filePath = "../assets/textures/map/BasicBlue.png";
    SDL_Texture* blueCubeTexture = AssetLoader::loadTexture(m_renderer.getRenderer(), filePath);
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            m_gameData.addTile(blueCubeTexture);
        }
    }

    nfo("Engine initialised successfully");
}

// TODO
void Engine::run() {
    // still need to handle cycle length properly to get desired FPS, this has been
    // done for now with SDL_RENDERER_PRESENTVSYNC flag in the SDL_Renderer
    while (m_gameData.running()) {
        m_eventHandler.processEvents(m_gameData);
        update();
        render();
    }
}

void Engine::update() {
    m_eventHandler.processEvents(m_gameData);

    // still need to do updates on everything else in the game such as camera and entities
    m_gameData.updateRunning();
    m_gameData.updateCamera();
    m_gameData.updateMap();
    m_gameData.updateEntities();
}

// TODO
void Engine::render() {
    // clear screen
    m_renderer.clear();

    // render map
    m_gameData.renderMap(m_renderer);

    // render entities
    m_gameData.renderEntities(m_renderer);

    // render ui
    // skip

    // swap buffers - present frame
    m_renderer.present();
}


} // namespace sle
