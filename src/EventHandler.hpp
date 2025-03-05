#pragma once
#include "math.hpp"
#include "slog.hpp"
#include <SDL_events.h>
#include <queue>

#include "GameData.hpp"

namespace sle {
class EventHandler {
private:
    static void handleMouseMotion(const SDL_Event &event, GameData &gameData);

public:
    static void input(GameData &gameData);
};

} // namespace sle
