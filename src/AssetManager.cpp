#include "AssetManager.hpp"

namespace sle {

ref<Texture> getDefaultTexture() {

}

ref<Texture> AssetManager::texture(const Renderer &ren, const std::filesystem::path &filePath) {
    // Texture already exists, just return it
    if (m_textures.contains(filePath) && !m_textures[filePath].expired()) { // short circuit eval :)
        return m_textures[filePath].lock();
    }

    SDL_Surface* tempSurface = IMG_Load(filePath.string().c_str());
    if (!tempSurface) {
        wrn("Could not load img from given filePath. {}", IMG_GetError());
    }

    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(ren.getRenderer(), tempSurface);
    if (!sdlTexture) {
        SDL_FreeSurface(tempSurface);
        wrn("Could not create texture from surface. {}", SDL_GetError());
        return getDefaultTexture();
    }

    ref<Texture> texture = std::make_shared<Texture>(sdlTexture);
    m_textures[filePath] = texture;
    SDL_FreeSurface(tempSurface);
    dbg("Texture loaded successfully {}", filePath);

    return texture;
}


} // namespace sle
