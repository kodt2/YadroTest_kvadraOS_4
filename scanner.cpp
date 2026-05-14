#include <filesystem>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "scanner.h"
#include "config.h"

namespace fs = std::filesystem;
namespace media_scanner {
    Scanner::FoundFiles Scanner::scan_directory(const ConfigManager& config) const {

        FoundFiles found;

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

                    if (ext.audio.count(ext_str)) {
                        found.found_audio.push_back(entry.path().filename().string());
                    } else if (ext.video.count(ext_str)) {
                        found.found_video.push_back(entry.path().filename().string());
                    } else if (ext.images.count(ext_str)) {
                        found.found_images.push_back(entry.path().filename().string());
                    }
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
            throw;
        }
        return found;
    }
} // media_scanner