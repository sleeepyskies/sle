#pragma once

#include <SDL_render.h>
#include <SDL_image.h>
#include <string>
#include "slog.hpp"
#include "Renderer.hpp"
#include "Tile.hpp"

class AssetLoader {
public:
    static SDL_Texture* loadTexture(SDL_Renderer *ren, const std::string& filePath);
};
