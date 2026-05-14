#include <filesystem>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "scanner.h"
#include "config.h"

namespace fs = std::filesystem;
namespace media_scanner {
    nlohmann::json Scanner::scan_directory(const ConfigManager& config) const {

        nlohmann::json result;
        result["audio"] = nlohmann::json::array();
        result["video"] = nlohmann::json::array();
        result["images"] = nlohmann::json::array();

        std::string target_dir = config.get_target_directory();
        const auto& ext = config.get_extensions();

        try {
            auto iterator = fs::recursive_directory_iterator(
                target_dir, 
                fs::directory_options::skip_permission_denied
            );

            for (const auto& entry : iterator) {
                if (entry.is_regular_file()) {
                    std::string ext_str = entry.path().extension().string();
                    std::transform(ext_str.begin(), ext_str.end(), ext_str.begin(),
                            [](unsigned char c) { return std::tolower(c); });
                    
                    std::string filename = entry.path().filename().string();

                    if (ext.audio.count(ext_str)) {
                        result["audio"].push_back(filename);
                    } else if (ext.video.count(ext_str)) {
                        result["video"].push_back(filename);
                    } else if (ext.images.count(ext_str)) {
                        result["images"].push_back(filename);
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
            throw;
        }
        return result;
    }
} // media_scanner