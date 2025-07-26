#pragma once

#include "AssetManager.hpp"
#include "files.hpp"
#include "secs/secs.hpp"
#include "types.hpp"
#include <functional>
#include <sstream>

#include "CameraComponent.hpp"
#include "TextureComponent.hpp"
#include "TransformComponent.hpp"

#include "CameraSystem.hpp"
#include "RenderSystem.hpp"

namespace sle {

/// @brief Type of a parser for a specific component.
using ComponentParser = std::function<uref<secs::Component>(const std::string&, AssetManager& am)>;

/// @brief Creates a registry of all available ComponentParsers.
/// Parsers for new components must be defined and added here.
hashmap<std::string, ComponentParser> createComponentParser() {
    hashmap<std::string, ComponentParser> parser{};

    // --------------------- PARSERS ---------------------
    parser["CameraComponent"] = [](const std::string& line, AssetManager& am) {
        std::istringstream iss(line);
        std::string marker{};
        float speed;

        iss >> marker >> speed;
        return makeUref<CameraComponent>(speed);
    };

    parser["TextureComponent"] = [](const std::string& line, AssetManager& am) {
        std::istringstream iss(line);
        std::string marker{};
        std::string fileName;

        iss >> marker >> fileName;
        TextureIndex idx = am.loadTexture(fileName);
        return makeUref<TextureComponent>(idx);
    };

    parser["TransformComponent"] = [](const std::string& line, AssetManager& am) {
        std::istringstream iss(line);
        std::string marker{};
        int x, y;

        iss >> marker >> x >> y;
        glm::ivec2 pos{ x, y };
        return makeUref<TransformComponent>(pos);
    };

    return parser;
}

} // namespace sle
