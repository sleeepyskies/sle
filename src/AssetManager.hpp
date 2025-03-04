#pragma once

#include <SDL_render.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include "core.hpp"
#include "slog.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include <filesystem>
#include <memory>

namespace sle {

/**
 * @brief This class is responsible for loading and handling all assets used in sle.
 *
 * Currently, the AssetManager will only hold wrefs to any assets used. This is to make sure
 * any assets that are no longer being used are freed up automatically, whilst still retaining
 * the ability to hand out refs.
 */
class AssetManager {
private:
    /// @brief A mapping of file path to Texture wref.
    std::unordered_map<std::filesystem::path, wref<Texture>> m_textures;

    /// @brief Creates a default texture to avoid unloaded textures on fail.
    ref<Texture> getDefaultTexture();
public:
    AssetManager() = default;
    ~AssetManager() = default;

    /**
     * This function will first check if an asset has already been loaded and return it. If it has
     * not been loaded yet, it will create this @ref Texture and keep a wref for itself. The caller
     * then has ownership of the texture.
     *
     * @param ren The current Renderer, since it is required by SDL to make an SDL_Texture.
     * @param filePath The filepath to the texture to be loaded.
     * @return A cref to the texture.
     */
    ref<Texture> texture(const Renderer &ren, const std::filesystem::path &filePath);

};

} // namespace sle
