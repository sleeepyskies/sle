#pragma once

#include <SDL.h>
#include "core.hpp"
#include "slog.hpp"

namespace sle {

/**
 * @brief Texture serves as a wrapper for the SDL_Texture, since it is an opaque class using raw pointers.
 */
class Texture {
private:
    /// @brief The underlying texture from the SDL library.
    SDL_Texture* m_texture;

public:
    /// @brief Make sure we cannot use the default constructor
    Texture() = delete;
    /// @brief Make sure we cannot use the copy constructor
    Texture(const Texture&) = delete;
    /// @brief Make sure we cannot use copy assignment
    Texture& operator= (const Texture&) = delete;

    /// @brief Make sure we must construct Texture explicitly
    explicit Texture(SDL_Texture* texture): m_texture(texture) {}

    /// @brief Make sure to clean up the underlying SDL_Texture* when destructing. Only perform if not nullptr
    ~Texture() {
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
        } else {
            wrn("This texture has already been destroyed.");
        }
    }

    /// @brief Getter method for the SDL_Texture*
    SDL_Texture* texture() const { return m_texture; }

    /// @brief Allow checking if the texture is still valid
    explicit operator bool() const { return m_texture != nullptr; }

};

} // namespace sle
