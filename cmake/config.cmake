
file(WRITE "${CMAKE_BINARY_DIR}/config.h"
"#pragma once

#define PROJECT_ROOT \"${CMAKE_SOURCE_DIR}\"
#define ASSETS_PATH \"${CMAKE_SOURCE_DIR}/assets\"
")



include_directories("${CMAKE_BINARY_DIR}")
