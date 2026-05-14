#include <chrono>

#include "config.h"
#include "server.h"
#include "periodic.h"
#include "scanner.h"

namespace media_scanner {
    PeriodicScanner::PeriodicScanner(const ConfigManager& config, MediaServer& server)
        : cfg(config), srv(server) {}

    PeriodicScanner::~PeriodicScanner() {
        stop();
    }

    void PeriodicScanner::start() {
        if (!running.exchange(true)) {
            worker = std::thread(&PeriodicScanner::run, this);
        }
    }

    void PeriodicScanner::stop() {
        if (running.exchange(false)) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void PeriodicScanner::run() {
        Scanner scanner;
        while (running) {
            nlohmann::json scan_res = scanner.scan_directory(cfg);
            srv.update_data(scan_res);
            std::this_thread::sleep_for(std::chrono::milliseconds(cfg.get_scan_interval()));
        }
    }
}