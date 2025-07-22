#pragma once

#include "Texture.hpp"
#include "Window.hpp"
#include "slog.hpp"
#include "types.hpp"
#include <SDL_image.h>
#include <SDL_render.h>
#include <filesystem>
#include <memory>
#include <string>

namespace sle {

const std::string MISSING_TEXTURE = "--missing-texture--";

/**
 *  TODO: add documentation, figure out a way to automatically handle cleanup when texture is not being used
 * anymore.
 */
class AssetManager {
public:
    AssetManager()  = default;
    ~AssetManager() = default;

    /// @brief Must be called before attempting to create any textures.
    void init(ref<Window> window);

    /**
     * @brief This function will load the texture at the given location. If it has already been loaded,
     * it will not load it again. Otherwise, it will create a new @ref Texture, store it and then return
     * its index.
     *
     * @param name The name of the file to load
     * @param filePath The filepath to the texture to be loaded.
     * @return The index of the loaded texture.
     */
    TextureIndex loadTexture(const std::string &name, const std::filesystem::path &filePath);

    /**
     * @brief This function return the @ref Texture at the given index.
     *
     * @param index The desired index.
     * @return The Texture at the given index.
     */
    Texture getByIndex(TextureIndex index);

private:
    std::vector<Texture> m_textureArray{};
    hashmap<std::string, TextureIndex> m_loaded{};

    /// @ref A pointer to the current window.
    ref<Window> m_window = nullptr;

    /// @brief A helper function to create a texture
    maybe<Texture> createTexture(const std::filesystem::path &filePath) const;
};

} // namespace sle
