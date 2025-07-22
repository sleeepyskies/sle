#pragma once

#include "ISceneSerializer.hpp"
#include "files.hpp"
#include <fstream>

namespace sle {

class TextSceneSerializer final : ISceneSerializer {
public:
    secs::Scene load(const std::string &filePath) override;

    void save(const secs::Scene &scene, const std::string &dirPath) override;
};

} // namespace sle

