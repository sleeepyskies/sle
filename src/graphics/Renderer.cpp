#include "Renderer.hpp"

namespace sle {

Renderer& Renderer::get() {
    static Renderer instance;
    return instance;
}

void Renderer::init(ref<Window> window) { m_window = window; }

void Renderer::stage(const size_t textureIndex, const glm::ivec2 position, const glm::ivec2 cameraPos) {
    m_staged.push_back(Renderable{ makeOffsetRect(cameraPos, position), textureIndex });
}

void Renderer::render(const ref<AssetManager>& am) {
    m_window->clear();

    for (const auto [rect, index] : m_staged) {
        const Texture& texture = am->getByIndex(index);
        m_window->render(texture, rect);
    }

    m_window->present();
}

} // namespace sle

