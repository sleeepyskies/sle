#pragma once

#include "Camera.hpp"
#include "EventHandler.hpp"
#include "TileMap.hpp"
#include "Window.hpp"

namespace sle {
class PlayState {
public:
    void loadMap(const TileMapResult &tmRes);

    void update(const InputData &inputData);

    void draw(const ref<Window> &ren) const;

private:
    Camera m_camera;
    TileMap m_map;
};

} // namespace sle
