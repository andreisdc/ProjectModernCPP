cmake_minimum_required(VERSION 3.1)

project(proiect_modern_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_Install OFF CACHE INTERNAL "")

#find_package(SDL2 REQUIRED)
#find_package(OpenGL REQUIRED)

#include_directories(${SDL2_INCLUDE_DIR})
#include_directories(${OPENGL_INCLUDE_DIR})

#add_subdirectory(third-party/imgui)
add_subdirectory(third-party/json)

add_executable(proiect_modern_cpp
        src/main.cpp
        src/County.hpp src/County.cpp
        src/Board.hpp src/Board.cpp
        src/User.cpp src/User.hpp)

target_link_libraries(proiect_modern_cpp
#		${SDL2_LIBRARIES}
#		${OPENGL_LIBRARIES}
#		imgui
		nlohmann_json::nlohmann_json)
