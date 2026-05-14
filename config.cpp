#include <string>
#include <unordered_set>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "config.h"


namespace media_scanner {

    ConfigManager::ConfigManager(const std::string& config_path){
        if (!load(config_path)){
            throw std::runtime_error("Critical: Could not load configuration file!");
        }

    }

    ConfigManager::ConfigManager() {}

    bool ConfigManager::load(const std::string& config_path){
        using json = nlohmann::json;

        std::ifstream file(config_path);

        if (!file.is_open()) {
            return false;
        }
        try {
            json j = json::parse(file);

            if (j.contains("extensions")) {
                auto& ext = j["extensions"];

                if (ext.contains("audio")) {
                    m_extensions.audio = ext["audio"].get<std::unordered_set<std::string>>();
                }
                if (ext.contains("video")) {
                    m_extensions.video = ext["video"].get<std::unordered_set<std::string>>();
                }
                if (ext.contains("images")) {
                    m_extensions.images = ext["images"].get<std::unordered_set<std::string>>();
                }
            }
            return true;
        } catch (const json::parse_error& e) {
            std::cerr << "JSON Parse error: " << e.what() << std::endl;
            return false;
        }
    }
} // namespace media_scanner