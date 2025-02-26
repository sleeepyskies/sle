#define SDL_MAIN_HANDLED
#include "Engine.hpp"
#include "slog.hpp"

int main() {
    // slog::logLevel = slog::Level::TRACE;

    // 0 on success
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        err("SDL could not init.", SDL_GetError());
        return 1;
    }
    nfo("SDL initialised successfully");

    // 0 on failure
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG ) == 0 ) {
        err("IMG could not init", IMG_GetError());
        return 1;
    }
    nfo("IMG initialised successfully");

    try {
        sle::Engine engine;
    } catch (const std::exception &e) {
        err("Engine could not init, exiting engine.", e.what());
        return 1;
    }
    return 0;
}
