#include <httplib.h>
#include <nlohmann/json.hpp>
#include "MediaServer.h"

namespace media_scanner {

    MediaServer::MediaServer() {
        current_data["audio"] = nlohmann::json::array();
        current_data["video"] = nlohmann::json::array();
        current_data["images"] = nlohmann::json::array();

        svr.Get("/media_files", [this](const httplib::Request&, httplib::Response& res) {
            std::lock_guard<std::mutex> lock(data_mutex);
            res.set_content(current_data.dump(), "application/json");
        });
    }

    void MediaServer::update_data(const nlohmann::json& new_data) {
        std::lock_guard<std::mutex> lock(data_mutex);
        current_data = new_data;
    }

    void MediaServer::start(int port) {
        svr.listen("0.0.0.0", port);
    }

    void MediaServer::stop() {
        svr.stop();
    }
}