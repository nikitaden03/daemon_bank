cmake_minimum_required(VERSION 3.21)
project(daemon_bank)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lcurl")

find_package(nlohmann_json 3.7.0 REQUIRED)

add_executable(daemon_bank main.cpp Parser/CParser.cpp Parser/CParser.h)

target_link_libraries(daemon_bank curl)
target_link_libraries(daemon_bank nlohmann_json::nlohmann_json)