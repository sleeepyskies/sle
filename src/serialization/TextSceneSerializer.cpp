#include "TextSceneSerializer.hpp"

namespace sle {

secs::Scene TextSceneSerializer::load(const std::string &filePath) { secs::Component comp; }

void TextSceneSerializer::save(const secs::Scene &scene, const std::string &dirPath) {
    std::ofstream file(scene.name());

    file.close();
}

} // namespace sle

