#pragma once
#include <queue>
#include <SDL_events.h>
#include "slog.hpp"
#include "math.hpp"

#include "GameData.hpp"

namespace sle {
class EventHandler {
private:
    static void handleMouseMotion(const SDL_Event &event, GameData &gameData);

public:
    void input(GameData &gameData) const;
};

} // namespace sle
