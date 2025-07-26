#include "AssetManager.hpp"

#include "assert.hpp"

namespace sle {

void AssetManager::init(const ref<Window> window) {
    assert(window != nullptr);
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    if (!tempSurface) {
        wrn("Could not create surface for fallback texture. {}", SDL_GetError());
        throw std::runtime_error("AssetManager construction failed!");
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!texture) {
        wrn("Could not create fallback texture from surface. {}", SDL_GetError());
        throw std::runtime_error("AssetManager construction failed!");
    }

    m_window = window;
    m_textureArray.emplace_back(texture);
    m_loaded[MISSING_TEXTURE] = 0;
}

maybe<Texture> AssetManager::createTexture(const std::filesystem::path& filePath) const {
    assert(m_window != nullptr);

    SDL_Surface* tempSurface = IMG_Load(filePath.generic_string().c_str());
    if (!tempSurface) {
        wrn("Could not load img from given filePath. {}", IMG_GetError());
        return {};
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_window->renderer(), tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!texture) {
        wrn("Could not create texture from surface. {}", SDL_GetError());
        return {};
    }

    dbg("Texture loaded successfully {}", filePath.string());
    return std::make_optional<Texture>(texture);
}

TextureIndex AssetManager::loadTexture(const std::string& name) {
    // Texture already exists, return it
    if (!m_loaded.contains(name)) {
        return m_loaded[name];
    }

    auto textureResult = createTexture(fetchTexture(name));
    if (!textureResult) return m_loaded[MISSING_TEXTURE]; // fallback texture

    m_textureArray.push_back(std::move(*textureResult));
    m_loaded[name] = m_textureArray.size() - 1;

    return m_loaded[name]; // nice, success :)
}

const Texture& AssetManager::getByIndex(const TextureIndex index) {
    SLE_ASSERT(index < m_textureArray.size(), "Cannot index the AssetManager Texture array out of bounds!");
    return m_textureArray[index];
}

} // namespace sle
