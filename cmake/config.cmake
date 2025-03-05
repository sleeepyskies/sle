
file(WRITE "${CMAKE_BINARY_DIR}/config.h"
"#pragma once

// this file is generated, do not change any content in this file as it will be overwritten the
// next time the project builds. Changes to this file can be made in cmake/config.cmake

const std::filesystem::path PROJECT_ROOT = \"${CMAKE_SOURCE_DIR}\";
const std::filesystem::path ASSETS_PATH = \"${CMAKE_SOURCE_DIR}/assets\";
")



include_directories("${CMAKE_BINARY_DIR}")
