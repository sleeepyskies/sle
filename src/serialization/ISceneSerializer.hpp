#pragma once
#include "AssetManager.hpp"
#include <secs/Scene.hpp>
#include <string>

namespace sle {

class ISceneSerializer {
public:
    virtual ~ISceneSerializer() = default;

    /**
     * @brief Loads the @ref secs::Scene from the provided filepath, and returns a Scene instance.
     *
     * @param filepath The filePath to the scene file is located at.
     */
    virtual secs::Scene load(const std::string& filepath, AssetManager& am) = 0;

    /**
     * @brief Saves the given scene in the given directory using the scenes name as the filename.
     *
     * @param scene The scene to save.
     * @param dirPath The directory in which the scene should be saved into.
     */
    virtual void save(secs::Scene& scene, const std::string& dirPath) = 0;
};

} // namespace sle
