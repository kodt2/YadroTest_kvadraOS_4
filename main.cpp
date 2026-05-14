
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <iostream>

#include "config.h"
#include "parser.h"
#include "scanner.h"

using namespace media_scanner;


    int main(int argc, const char* argv[]){
        try {
            Parser parser;
            auto args = parser.parse_cmd_args(argc, argv);

            ConfigManager config;

            if (!args.config_path.empty()) {
                config = ConfigManager(args.config_path);
            }

            config.set_scan_interval(args.scan_interval);

            if (!args.target_dir.empty()) {
                config.set_target_directory(args.target_dir);
            } else {
                const char* home = std::getenv("HOME");
                if (home) {
                    config.set_target_directory(home);
                }
            }
            
            Scanner scanner;
            auto files = scanner.scan_directory(config);

            std::cout << scanner.scan_directory(config) << std::endl;


        }
        catch(const std::exception& e){
            std::cerr << "Startup Error: " << e.what() << std::endl;
            return 1;
        }
        return 0;
    }
