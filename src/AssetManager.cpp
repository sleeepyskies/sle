#include "AssetManager.hpp"

namespace sle {

AssetManager::AssetManager(const cref<Renderer> &ren) {
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,1,1,32,0,0,0,0);;
    if (!tempSurface) {
        wrn("Could not create surface for fallback texture. {}", SDL_GetError());
        throw std::runtime_error("AssetManager construction failed");
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren->getRenderer(), tempSurface);
    if (!texture) {
        SDL_FreeSurface(tempSurface);
        wrn("Could not create fallback texture from surface. {}", SDL_GetError());
        throw std::runtime_error("AssetManager construction failed");
    }

    m_renderer = ren;
    m_textures[MISSING_TEXTURE] = std::make_shared<Texture>(texture);
}

ref<Texture> AssetManager::texture(const std::filesystem::path &filePath) {
    // Texture already exists, just return it
    if (m_textures.contains(filePath) && !m_textures[filePath].expired()) { // short circuit eval :)
        return m_textures[filePath].lock();
    }

    SDL_Surface* tempSurface = IMG_Load(filePath.string().c_str());
    if (!tempSurface) {
        wrn("Could not load img from given filePath. {}", IMG_GetError());
    }

    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(m_renderer->getRenderer(), tempSurface);
    if (!sdlTexture) {
        SDL_FreeSurface(tempSurface);
        wrn("Could not create texture from surface. {}", SDL_GetError());
        return m_textures[MISSING_TEXTURE].lock();
    }

    ref<Texture> texture = std::make_shared<Texture>(sdlTexture);
    m_textures[filePath] = texture;
    SDL_FreeSurface(tempSurface);
    dbg("Texture loaded successfully {}", filePath);

    return texture;
}

} // namespace sle
