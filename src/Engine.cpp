#include "Engine.hpp"

namespace sle {
Engine::Engine(): m_gameData(), m_eventHandler(), m_renderer() {
    init();
    run();
}

Engine::~Engine() {
    SDL_Quit();
    IMG_Quit();
    nfo("Engine has shutdown.");
}

void Engine::init() {
    const std::string filePath = "../assets/textures/map/Blue-Iso-Tile.png";
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
    // still need to handle cycle length properly to get desired FPS
    while (m_running) {
        trc("Current tick", SDL_GetTicks());

        readInput();
        update();
        render();
    }
}

// TODO
void Engine::readInput() {
    trc("Reading Inp");
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_running = false;
            break;
        }
        // Give event to event handler.
        // something like:
        // m_eventHandler.handle(m_gameData , event, event.type);
        // or something like
        // m_eventHandler.enqueueEvent(event, event.type)
    }
}

// TODO
void Engine::update() {
    m_eventHandler.processEvents(m_gameData);

    // still need to do updates on everything else in the game such as camera and entities
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
