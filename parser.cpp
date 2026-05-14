#include "parser.h"
#include <filesystem>
#include <sstream>
#include <stdexcept>

namespace media_scanner {
    Parser::FileInfo Parser::parse_file_name(const std::string& name) {
        std::filesystem::path p(name);
        return { p.stem().string(), p.extension().string() };
    }
    
    std::vector<std::string> Parser::prepare_cmd_args(const int size, char* cmd_args[]){
        std::vector<std::string> res;
        for (int i=0;i<size;i++){
            res.push_back(std::string(cmd_args[i]));
        }
        return res;
    }

    Parser::CmdArgs Parser::parse_cmd_args(const int size, char* cmd_args[]){
        CmdArgs res;

        std::vector<std::string> cmd_strings = prepare_cmd_args(size, cmd_args);
        
        for (int i =1; i<cmd_strings.size();i++){

            if (cmd_strings[i]== "--config"){
                if (i+1<cmd_strings.size()){
                    if (validate_args("--config",cmd_strings[i+1])){
                        res.config_path = cmd_strings[++i];
                    } else{
                        throw std::runtime_error("Invalid argument for --config");
                    }
                } else {
                    std::cerr << "Error: --config requires a value" << std::endl;
                    throw std::runtime_error("Missing value for --config");
                }
            }
            else if (cmd_strings[i] == "--interval") {
                if (i+1<cmd_strings.size()){
                    if (validate_args("--interval",cmd_strings[i+1])){
                        res.scan_interval = std::stoi(cmd_strings[++i]);
                    } else{
                        throw std::runtime_error("Invalid argument for --interval");
                    }
                } else {
                    std::cerr << "Error: --interval requires a value" << std::endl;
                    throw std::runtime_error("Missing value for --interval");
                }
            }

            else if (cmd_strings[i] == "--target"){
                if (i+1<cmd_strings.size()){
                    if (validate_args("--target",cmd_strings[i+1])){
                        res.target_dir = cmd_strings[++i];
                    } else{
                        throw std::runtime_error("Invalid argument for --target");
                    }
                } else {
                    std::cerr << "Error: --target requires a value" << std::endl;
                    throw std::runtime_error("Missing value for --target");
                }
            }
        }
        return res;
    }

    bool Parser::validate_args(const std::string& flag, const std::string& arg) const{
        if (arg.size() >= 2 && arg.substr(0, 2) == "--") {
            std::cerr << "Error: Argument for " << flag << " cannot be another flag!" << std::endl;
            return false;
        }

        if (flag == "--config" || flag == "--target") {
            if (!std::filesystem::exists(arg)) {
                std::cerr << "Error: Path " << arg << " does not exist!" << std::endl;
                return false;
            }

        }

        if (flag == "--target" && !std::filesystem::is_directory(arg)){
            std::cerr << "Error: --target requires a path to a directory, not a file!" << std::endl;
            return false;
        }

        if (flag == "--interval"){
            try {
                int value = std::stoi(arg);
                if (value <= 0) {
                    std::cerr << "Error: Interval must be a positive number! (ms)" << std::endl;
                    return false;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Error: --interval value '" << arg << "' is not a number!" << std::endl;
                return false;
            }
        }

        return true;     
    }
} //media_scanner


