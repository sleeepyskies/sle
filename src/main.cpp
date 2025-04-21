#define SDL_MAIN_HANDLED
#include "Engine.hpp"
#include "secs/secs.hpp"

int main() {
    // slog::logLevel = slog::Level::TRACE;

    sle::Engine engine{};
    engine.init();
    engine.run();
    engine.shutdown();

    return 0;
}
