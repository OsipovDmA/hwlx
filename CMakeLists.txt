cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(main main.cpp)

include(CTest)

target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)



