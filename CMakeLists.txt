cmake_minimum_required(VERSION 3.16)
project(hyprland-toggle-tiling VERSION 1.4.3 LANGUAGES CXX)
include(GNUInstallDirs)
include(FetchContent)
option(USE_SYSTEM_JSON "Use system nlohmann_json" ON)

if(USE_SYSTEM_JSON)
	find_package(nlohmann_json REQUIRED)
else() 
	FetchContent_Declare(
		json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz 
		)
	FetchContent_MakeAvailable(json)
endif()

add_executable(htt src/main.cpp src/HyprlandService.cpp
				   src/Workspace.cpp src/ShellService.cpp
				   src/FileService.cpp src/WindowRule.cpp src/Client.cpp
				   )

target_compile_features(htt PRIVATE cxx_std_17)
target_link_libraries(htt PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(htt PRIVATE ${PROJECT_SOURCE_DIR}/src)
install(TARGETS htt RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )
