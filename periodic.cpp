#include <chrono>

#include "config.h"
#include "server.h"
#include "periodic"

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
            nlohmann::json scan_res = scanner.scan(cfg.get_target_directory(), cfg.get_extensions());
            srv.update_data(scan_res);
            std::this_thread::sleep_for(std::chrono::milliseconds(cfg.get_scan_interval()));
        }
    }
}