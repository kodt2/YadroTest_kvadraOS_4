#ifndef MEDIA_SERVER_H
#define MEDIA_SERVER_H

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <mutex>

namespace media_scanner {

    class MediaServer {
    public:
        MediaServer();
        void update_data(const nlohmann::json& new_data);
        void start(int port);
        void stop();

    private:
        httplib::Server svr;
        nlohmann::json current_data;
        std::mutex data_mutex;
    };

}

#endif