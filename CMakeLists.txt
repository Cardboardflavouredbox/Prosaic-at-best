cmake_minimum_required(VERSION 3.3)
project(Prosaic_at_best LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Prosaic_at_best src/main.cpp)
target_compile_features(Prosaic_at_best PRIVATE cxx_std_17)
target_link_libraries(Prosaic_at_best PRIVATE SFML::Graphics SFML::Network)