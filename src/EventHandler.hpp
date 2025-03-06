#pragma once
#include "math.hpp"
#include "slog.hpp"
#include <SDL_events.h>
#include <queue>

#include "GameData.hpp"

namespace sle {
class EventHandler {
private:
    void handleMouseMotion(const SDL_Event &event, GameData &gameData);

public:
    void input(GameData &gameData);
};

} // namespace sle
