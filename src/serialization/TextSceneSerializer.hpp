#pragma once

#include "ComponentParser.hpp"
#include "ISceneSerializer.hpp"
#include "assert.hpp"
#include "config.h"
#include "files.hpp"
#include "strings.hpp"
#include "types.hpp"
#include <fstream>
#include <sstream>

namespace sle {

/**
 * @brief This is used for loading and saving scene files in standard text format.
 * These files are stored in a regular .txt format. An example file may look like:
 * E 0
 * E 1
 * E 2
 * E 3
 * E 4
 * E 5
 * E 6
 * C 0 1 8 7
 *	Texture filepath/to/texture
 * C 4
 * 	Camera 0.46
 * C 3
 * 	Transform (90,14)
 * S
 * 	CameraSystem
 * S
 * 	RenderSystem
 */
class TextSceneSerializer final : ISceneSerializer {
private:
    /**
     * @brief A simple struct used for passing around any relevant
     * context when parsing a new scene.
     */
    struct ParsingContext {
        /// @brief Maps the entity ID in the file to the actual scenes entity.
        hashmap<uint32_t, secs::Entity> parsedEntities{};
        hashmap<std::string, ComponentParser> componentParser = createComponentParser();
    };

    /**
     * @brief A simple struct holding parsed header information obtained from
     * parsing a file.
     */
    // struct ParsingConfiguration {};

public:
    secs::Scene load(const std::string& filePath, AssetManager& am) override;

    void save(secs::Scene& scene, const std::string& dirPath) override;

private:
    /// @brief Will parse an entity and update the given scene accordingly.
    void parseEntity(std::istringstream& iss, ParsingContext& parsingContext, secs::Scene& scene);
    /// @brief Will parse a component and update the given scene accordingly.
    void parseComponent(std::istringstream& iss, std::ifstream& file, ParsingContext& parsingContext,
                        secs::Scene& scene, AssetManager& am);
    /// @brief Will parse a system and update the given scene accordingly.
    void parseSystem(std::ifstream& file, secs::Scene& scene);
};

} // namespace sle

