cmake_minimum_required(VERSION 3.1)

project(proiect_modern_cpp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(third-party/json)

add_executable(proiect_modern_cpp src/main.cpp src/inc/user/user.cpp src/inc/user/user.h)
target_link_libraries(proiect_modern_cpp PRIVATE nlohmann_json::nlohmann_json)
