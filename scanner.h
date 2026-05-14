#ifndef SKANER_HPP
#define SKANER_HPP

#include <filesystem>
#include <vector>
#include <string>

#include "config.h"

namespace media_scanner {
    class Scanner{
    public:
        struct FoundFiles{
            std::vector<std::string> found_audio;
            std::vector<std::string> found_video;
            std::vector<std::string> found_images;
        };

        FoundFiles scan_directory(const ConfigManager& config) const;

    };
} //media_scanner
#endif // SKANER_HPP