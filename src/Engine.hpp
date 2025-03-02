#pragma once

#include <stdexcept>
#include "SDL.h"
#include "SDL_image.h"
#include "slog.hpp"
#include "Renderer.hpp"
#include "GameData.hpp"
#include "EventHandler.hpp"
#include "AssetLoader.hpp"

namespace sle {
class Engine {
private:
    Renderer m_renderer;
    GameData m_gameData;
    EventHandler m_eventHandler;

    void update();
    void render();

public:
    Engine();
    ~Engine();

    void init();

    void run();

};
;
} // namespace sle
