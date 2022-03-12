cmake_minimum_required(VERSION 3.19)

set(VCPKG_CMAKE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_CMAKE})

project(catch_benchmarks_run)
set(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

set(SOURCE_FILES main.cpp)

#add_definitions(-DBUILD_STATIC)

find_package(benchmark CONFIG REQUIRED)
link_libraries(benchmark::benchmark benchmark::benchmark_main)

add_executable(catch_benchmarks_run ${SOURCE_FILES})

target_link_libraries(catch_benchmarks_run detector_core)