#include "TextSceneSerializer.hpp"

namespace sle {

secs::Scene TextSceneSerializer::load(const std::string& sceneName, AssetManager& am) {
    std::ifstream file(TEXT_SCENE_PATH / sceneName);
    std::string line{};
    secs::Scene scene{};
    ParsingContext parsingContext{};

    char marker;
    while (std::getline(file, line)) {
        trim(line);
        std::istringstream iss{ line };

        // need at least 3 chars
        SLE_ASSERT(line.size() >= 3, "Not enough characters to correctly indicate a marker, aborting parsing");

        iss >> marker;

        if (marker == 'E') parseEntity(iss, parsingContext, scene);
        if (marker == 'C') parseComponent(iss, file, parsingContext, scene, am);
        if (marker == 'S') parseSystem(file, scene);
    }

    file.close();

    return scene;
}

void TextSceneSerializer::parseEntity(std::istringstream& iss, ParsingContext& parsingContext, secs::Scene& scene) {
    uint32_t parsedEntityID;
    iss >> parsedEntityID;

    SLE_ASSERT(!parsingContext.parsedEntities.contains(parsedEntityID),
               "Parsed Entity already exists. Scen file invalid, aborting parsing.");

    const secs::Entity e                          = scene.createEntity();
    parsingContext.parsedEntities[parsedEntityID] = e;
}

void TextSceneSerializer::parseComponent(std::istringstream& iss, std::ifstream& file, ParsingContext& parsingContext,
                                         secs::Scene& scene, AssetManager& am) {
    std::vector<secs::Entity> componentEntities{};

    while (iss) {
        uint32_t eid;
        iss >> eid;
        SLE_ASSERT(parsingContext.parsedEntities.contains(eid),
                   "The entity for this component has not been defined (yet), aborting parsing.");
        componentEntities.push_back(parsingContext.parsedEntities[eid]);
    }

    std::string line;
    std::getline(file, line);
    uref<secs::Component> component = parsingContext.componentParser["CameraComponent"](trim(line), am);

    for (auto e : componentEntities) {
        scene.registerComponent<decltype(component)>(e, component, componentEntities.size() == 1);
    }
}

void TextSceneSerializer::parseSystem(std::ifstream& file, secs::Scene& scene) {
    std::string line;
    std::getline(file, line);
    trim(line);

    if (line == "CameraSystem")
        scene.registerSystem<CameraSystem>();
    else if (line == "RenderSystem")
        scene.registerSystem<RenderSystem>();
}

void TextSceneSerializer::save(secs::Scene& scene, const std::string& dirPath) {
    std::ofstream file(scene.name());

    file.close();
}

} // namespace sle

