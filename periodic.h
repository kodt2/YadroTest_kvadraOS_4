#ifndef PERIODIC_SCANNER_H
#define PERIODIC_SCANNER_H

#include "config.h"
#include "server.h"
#include <thread>
#include <atomic>

namespace media_scanner {

class PeriodicScanner {
public:
    PeriodicScanner(const ConfigManager& config, MediaServer& server);
    ~PeriodicScanner();
    void start();
    void stop();

private:
    void run();

    const ConfigManager& cfg;
    MediaServer& srv;
    std::thread worker;
    std::atomic<bool> running{false};
};

}

#endif