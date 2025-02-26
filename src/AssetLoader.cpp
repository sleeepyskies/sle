#include "AssetLoader.hpp"

SDL_Texture* AssetLoader::loadTexture(SDL_Renderer *ren, const std::string &filePath) {
    SDL_Surface *tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        wrn("Could not load img from given filePath,", IMG_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tempSurface);
    if (!texture) {
        wrn("Could not create texture from surface,", SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(tempSurface);

    dbg("Texture loaded successfully", filePath);
    return texture;
}
