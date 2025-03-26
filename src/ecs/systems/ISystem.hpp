#pragma once

namespace sle {

class Scene;

/**
 * @brief The interface that all systems must implement. Allows for the data held in Component
 * objects to be changed dynamically during the runtime of the engine.
 */
class ISystem {
public:
    /// @brief Handles updating this systems logic.
    virtual void update(float deltaTime, const Scene &scene) = 0;
};

} // namespace sle
