cmake_minimum_required(VERSION 3.31.5)
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

if (WIN32)
    add_library(myLib SHARED ${SOURCE_FILES})
    set(CMAKE_EXE_LINKER_FLAGS " -static")
    target_link_libraries(myLib -static-libgcc -static-libstdc++)
    add_executable(Prosaic_at_best WIN32 src/main.cpp)
else()
    add_executable(Prosaic_at_best src/main.cpp)
endif ()
target_compile_features(Prosaic_at_best PRIVATE cxx_std_17)
target_link_libraries(Prosaic_at_best PRIVATE SFML::Graphics SFML::Network SFML::Audio)