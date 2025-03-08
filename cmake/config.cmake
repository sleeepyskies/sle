
file(WRITE "${CMAKE_BINARY_DIR}/config.h"
"#pragma once

// this file is generated, do not change any content in this file as it will be overwritten the
// next time the project builds. Changes to this file can be made in cmake/config.cmake

#include <filesystem>
#include <unordered_set>

const std::filesystem::path PROJECT_ROOT = \"${CMAKE_SOURCE_DIR}\";
const std::filesystem::path ASSETS_PATH = \"${CMAKE_SOURCE_DIR}/assets\";

const std::unordered_set<std::string> VALID_TILES = {\n")

# generate VALID_TILES
file(GLOB TILE_FILES "${CMAKE_SOURCE_DIR}/assets/textures/map/*")
foreach (tile IN LISTS TILE_FILES)
    get_filename_component(filename ${tile} NAME)
    file(APPEND "${CMAKE_BINARY_DIR}/config.h"
            "    \"${filename}\",\n")
endforeach ()
file(APPEND "${CMAKE_BINARY_DIR}/config.h"
        "};\n")


include_directories("${CMAKE_BINARY_DIR}")
