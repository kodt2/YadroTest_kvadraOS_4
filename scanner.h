#ifndef SKANER_HPP
#define SKANER_HPP

#include <filesystem>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "config.h"

namespace media_scanner {
    class Scanner{
    public:

        nlohmann::json scan_directory(const ConfigManager& config) const;

    };
} //media_scanner
#endif // SKANER_HPP