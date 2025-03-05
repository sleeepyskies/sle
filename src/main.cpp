#define SDL_MAIN_HANDLED
#include "Engine.hpp"
#include "slog.hpp"

// Engine engine{};
// engine.init();
// engine.shutdown();

int main() {
    // slog::logLevel = slog::Level::TRACE;
    try {
        sle::Engine engine;
    } catch (const std::exception &e) {
        err("Engine could not init, exiting engine. {}", e.what());
        return 1;
    }
    return 0;
}
