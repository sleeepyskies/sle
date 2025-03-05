#pragma once

#include "Constants.hpp"
#include "slog.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>

namespace sle {
class Renderer {
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

public:
    Renderer();
    ~Renderer();

    void clear() const;
    void present() const;

    SDL_Renderer *renderer() const { return m_renderer; }
};

} // namespace sle
