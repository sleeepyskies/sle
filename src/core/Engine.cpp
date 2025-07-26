#include "Engine.hpp"

namespace sle {

void Engine::init() {
    initSDL();

    const auto window = std::make_shared<Window>();
    m_assetManager    = std::make_shared<AssetManager>();
    m_assetManager->init(window);
    Renderer::get().init(window);

    TextSceneSerializer tss{};
    m_scene = tss.load("test.txt", *m_assetManager);
}

void Engine::initSDL() const {
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

void Engine::run() {
    Uint64 now       = SDL_GetPerformanceCounter();
    Uint64 previous  = now;
    double deltaTime = 0;

    const double frequencyInv = 1000 / static_cast<double>(SDL_GetPerformanceFrequency());

    while (Input::get().running()) {
        previous  = now;
        now       = SDL_GetPerformanceCounter();
        deltaTime = (static_cast<double>(now) - static_cast<double>(previous)) * frequencyInv;

        Input::get().poll();
        m_scene.update(deltaTime);
        Renderer::get().render(m_assetManager);
    }
}

void Engine::shutdown() const {
    SDL_Quit();
    IMG_Quit();
    nfo("Engine has shutdown.");
}

} // namespace sle
