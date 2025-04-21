#pragma once

#include "Texture.hpp"
#include "Window.hpp"
#include "types.hpp"
#include "AssetManager.hpp"
#include "math.hpp"

namespace sle {

class Renderer {
public:
    /// @brief Returns the instance of Renderer.
    static Renderer &get();

    /// @brief Inits the Renderer. Must be called before making any render calls.
    void init(ref<Window> window);

    /// @brief Stages the given texture for rendering.
    void stage(size_t textureIndex, glm::ivec2 position, glm::ivec2 cameraPos);

    /// @brief Renders all the staged textures.
    void render(const ref<AssetManager> &am);

private:
    /// @brief Helper struct for simplifying code. Should only be used in @ref Renderer.hpp
    struct Renderable {
        SDL_Rect rect{};
        size_t textureIndex = 0;
    };

    /// Hide constructor
    Renderer() = default;

    /// @ref A pointer to the current window.
    ref<Window> m_window = nullptr;
    /// @ref All staged renderables.
    std::vector<Renderable> m_staged{};

};

} // namespace sle