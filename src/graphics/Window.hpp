#pragma once

#include "constants.hpp"
#include "slog.hpp"
#include "types.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>

namespace sle {
/**
 * @brief The Window class acts as a wrapper class for SDL_Renderer and SDL_Window. To draw anything,
 * this object must be used.
 */
class Window {
public:
    Window();
    ~Window();

    /// @brief Fills the SDL back buffer with the given color. Defaults to black.
    void clear(const Color &color = Color{ 0, 0, 0, 255 }) const;
    /// @brief Swaps the SDL buffers. Presents the back buffer image to the screen.
    void present() const;

    /// @brief Returns the SDL_Renderer.
    SDL_Renderer *renderer() const { return m_renderer; }

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
};

} // namespace sle
