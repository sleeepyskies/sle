#define SDL_MAIN_HANDLED
#include "Engine.hpp"

int main(int argc, char* argv[]) {
    slog::logLevel = slog::Level::TRACE;

    sle::Engine engine{};
    engine.init();
    engine.run();
    engine.shutdown();

    return 0;
}
