#pragma once
#include <config.h>
#include <filesystem>

namespace sle {

namespace fs = std::filesystem;

// ------------ file path handling --------------
/**
 * @brief Fetches the filename from assets/textures/map.
 * @param fileName The file to fetch the path of
 * @param fileExtension The extension of the file to fetch. Defaults to .png. Do not pass '.' here.
 */
inline fs::path fetchTileTexture(const std::string &fileName, const std::string &fileExtension = "png") {
    return ASSETS_PATH / "textures/map" / (fileName + "." + fileExtension);
}

/**
 * @brief Fetches the filename from assets/map-files.
 * @param fileName The file to fetch the path of
 * @param fileExtension The extension of the file to fetch. Defaults to .slemap. Do not pass '.' here.
 */
inline fs::path fetchMapFile(const std::string &fileName, const std::string &fileExtension = "slemap") {
    fs::path assetsDir = ASSETS_PATH / "map-files" / (fileName + "." + fileExtension);
}

} // namespace sle
