#include "EventHandler.hpp"

namespace sle {

void EventHandler::input(GameData &gameData) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                gameData.stop();
                break;
            case SDL_MOUSEMOTION:
                handleMouseMotion(event, gameData);
                break;
            case SDL_KEYDOWN:
                // 0 if not a key repeat
                if (event.key.repeat == 0) gameData.keyDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                gameData.keyUp(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void EventHandler::handleMouseMotion(const SDL_Event &event, GameData &gameData) {
    gameData.setMousePos(event.motion.x, event.motion.y);
    trc("Mouse is at position x: {}, y: {}", event.motion.x, event.motion.y);
}

} // namespace sle
