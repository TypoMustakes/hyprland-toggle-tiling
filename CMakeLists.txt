cmake_minimum_required(VERSION 3.16)

project(hyprland-toggle-tiling
    VERSION 1.4.2
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(FetchContent)

# --------------------------------------------------
# Dependency handling
# --------------------------------------------------

option(USE_SYSTEM_JSON
    "Use system-installed nlohmann_json instead of fetching"
    OFF
)

if(USE_SYSTEM_JSON)
    find_package(nlohmann_json CONFIG REQUIRED)
else()
    # Try system package first silently
    find_package(nlohmann_json CONFIG QUIET)

    if(NOT nlohmann_json_FOUND)
        message(STATUS "nlohmann_json not found, fetching from GitHub")

        FetchContent_Declare(
            nlohmann_json
            URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        )

        FetchContent_MakeAvailable(nlohmann_json)
    else()
        message(STATUS "Using system nlohmann_json")
    endif()
endif()

# --------------------------------------------------
# Executable
# --------------------------------------------------

add_executable(htt
    src/main.cpp
    src/HyprlandService.cpp
    src/Workspace.cpp
    src/ShellService.cpp
    src/FileService.cpp
    src/WindowRule.cpp
    src/Client.cpp
)

target_compile_features(htt PRIVATE cxx_std_17)

target_link_libraries(htt
    PRIVATE
        nlohmann_json::nlohmann_json
)

target_include_directories(htt PRIVATE ${PROJECT_SOURCE_DIR}/src)

# --------------------------------------------------
# Install
# --------------------------------------------------

install(TARGETS htt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

