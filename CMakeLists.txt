cmake_minimum_required(VERSION 3.10.0)
project(hyprland-toggle-tiling VERSION 1.4.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(htt
	src/main.cpp
	src/HyprlandService.cpp
	src/Workspace.cpp
	src/ShellService.cpp
	src/FileService.cpp
	src/WindowRule.cpp
	src/Client.cpp)
target_link_libraries(htt PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(htt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
