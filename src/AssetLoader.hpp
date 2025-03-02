#pragma once

#include <SDL_render.h>
#include <SDL_image.h>
#include <string>
#include "slog.hpp"
#include "Renderer.hpp"

namespace sle {
class AssetLoader {
public:
    static SDL_Texture* loadTexture(SDL_Renderer *ren, const std::string& filePath);

    AssetLoader() = delete; // prevent instantiation
};

} // namespace sle
