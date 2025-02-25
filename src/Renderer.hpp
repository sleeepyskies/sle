#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include "slog.hpp"
#include "Constants.hpp"

class Renderer {
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

public:
    Renderer();
    ~Renderer();

    void clear() const;
    void present() const;

    SDL_Renderer* getRenderer() const { return m_renderer; }
};
