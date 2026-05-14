#include "config.h"
#include "parser.h"
#include "scanner.h"

namespace media_scanner {
    int main(int argc, char* argv){
        try {
            Parser parser;
            auto args = parser.parse_cmd_args(argc, argv);

            ConfigManager config;

            if (!args.config_path.empty()) {
                config = ConfigManager(args.config_path);
            }
            if (!args.scan_interval.empty()){
                config.set_scan_interval(args.scan_interval);
            }
            if (!args.target_dir.empty()){
                config.set_target_directory(args.target_dir);
            }
            
            Scanner scanner;
            scanner.scan_directory()

        }
        catch(const std::exception& e){
            std::cerr << "Startup Error: " << e.what() << std::endl;
            return 1;
        }
        return 0;
    }
}//media_scanner