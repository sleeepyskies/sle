#include "Engine.hpp"


namespace sle {

void Engine::init() {
    initSDL();

    ref<Window> window = std::make_shared<Window>();
    m_assetManager.init(window);

    auto mapResult = m_mapSerializer.load(m_assetManager, DEFAULT_MAP);
    if (!mapResult) throw std::runtime_error("Could not load a map, exiting the program.");
    ref<TileMap> tileMap = std::make_shared<TileMap>(*mapResult);

    // Create states we want to register, for now just MapEditor
    ref<MapEditorState> meState = std::make_shared<MapEditorState>(window, tileMap);
    m_state.registerState(meState);
}

void Engine::run() {
    // still need to handle cycle length properly to get desired FPS, this has been
    // done for now with SDL_RENDERER_PRESENTVSYNC flag in the SDL_Renderer
    bool running = true;
    while (running) {
        m_eventHandler.pollEvents();
        running = !m_eventHandler.engineData().quit;
        m_state.update(m_eventHandler.inputData());
        m_state.draw();
        m_state.stateChange();
    }
}

void Engine::shutdown() {
    SDL_Quit();
    IMG_Quit();
    nfo("Engine has shutdown.");
}

void Engine::initSDL() {
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
}

} // namespace sle
