#include <filesystem>
#include <unistd.h>
#include <limits.h>

namespace media_scanner {
    std::filesystem::path get_executable_dir()
    {
        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);

        if (count == -1) {
            throw std::runtime_error("Cannot resolve executable path");
        }

        buffer[count] = '\0';
        return std::filesystem::path(buffer).parent_path();
    }
}