cmake_minimum_required(VERSION 3.14)
project(media_scanner_server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.12.6
)
FetchContent_MakeAvailable(cpp-httplib)

find_package(Threads REQUIRED)

add_executable(media_scanner
    main.cpp
    config.cpp
    parser.cpp
    scanner.cpp
    server.cpp
    periodic.cpp
)

target_link_libraries(media_scanner
    PRIVATE
    nlohmann_json::nlohmann_json
    httplib::httplib
    Threads::Threads
)