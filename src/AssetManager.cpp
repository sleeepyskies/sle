#include "AssetManager.hpp"

namespace sle {

void AssetManager::init(const ref<Window> &window) {
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    if (!tempSurface) {
        wrn("Could not create surface for fallback texture. {}", SDL_GetError());
        throw std::runtime_error("AssetManager construction failed!");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->renderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!texture) {
        wrn("Could not create fallback texture from surface. {}", SDL_GetError());
        throw std::runtime_error("AssetManager construction failed!");
    }

    m_window = window;
    m_textures[MISSING_TEXTURE] = std::make_shared<Texture>(texture);
}

maybe<Texture> AssetManager::createTexture(const std::filesystem::path &filePath) const {
    assert(m_window != nullptr);

    SDL_Surface *tempSurface = IMG_Load(filePath.generic_string().c_str());
    if (!tempSurface) {
        wrn("Could not load img from given filePath. {}", IMG_GetError());
        return {};
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_window->renderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!texture) {
        wrn("Could not create texture from surface. {}", SDL_GetError());
        return {};
    }

    dbg("Texture loaded successfully {}", filePath.string());
    return std::make_optional<Texture>(texture);
}

ref<Texture> AssetManager::texture(const std::filesystem::path &filePath) {
    // Texture already exists, return it
    if (m_textures.contains(filePath) && !m_textures[filePath].expired()) { // short circuit eval :)
        return m_textures[filePath].lock();
    }

    auto textureResult = createTexture(filePath);
    if (!textureResult)
        return m_textures[MISSING_TEXTURE].lock(); // could not create, return default texture

    ref<Texture> textureRef   = std::make_shared<Texture>(std::move(*textureResult));
    wref<Texture> textureWref = textureRef;
    m_textures[filePath]      = textureWref;

    return textureRef; // nice, success :)
}

} // namespace sle
