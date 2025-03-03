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

    void render() const;

public:
    Engine();

    void run();

};
;
} // namespace sle
