#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <vector>

namespace media_scanner {
    class Parser{
    public:
        struct CmdArgs{
            std::string config_path = "config.json";
            int scan_interval = 5000;
            std::string target_dir = ".";
        };

        CmdArgs parse_cmd_args(const int size,const char* cmd_args[]) const;

        struct FileInfo{
            std::string file_name;
            std::string ext;
        };

        static FileInfo parse_file_name(const std::string& name);
    private:
        std::vector<std::string> prepare_cmd_args(const int size, const char* cmd_args[]) const;
        bool validate_args(const std::string& flag, const std::string& arg) const;
    };
}

#endif // PARSER_HPP