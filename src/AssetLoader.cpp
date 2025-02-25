#include "AssetLoader.hpp"

SDL_Texture* AssetLoader::loadTexture(SDL_Renderer *ren, const std::string &filePath) {
    SDL_Surface *tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        err("Could not load img from given filePath,", IMG_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tempSurface);
    if (!texture) {
        err("Could not create texture from surface,", SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(tempSurface);
    return texture;
}
