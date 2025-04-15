#pragma once

#include "EventHandler.hpp"
#include "System.hpp"

namespace secs {

class CameraSystem final : public System {
    void update(const double deltaTime, Scene &scene) override {
        // TODO: handle camera logic here lol
        sle::EventHandler::inputData()
    }
};

} // namespace secs