cmake_minimum_required(VERSION 3.19)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

if(DEFINED VCPKG_ROOT)
	message(VCPKG_ROOT：${VCPKG_ROOT})
else()	
IF (WIN32)
	MESSAGE(STATUS "Now is windows")
	set(VCPKG_ROOT F:/git/vcpkg)
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple system.")
	set(VCPKG_ROOT /Users/hualongzhang/work/vcpkg)
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()
ENDIF ()

option(USE_VCPKG "option for VCPKG" OFF)
message("option for USE_VCPKG ${USE_VCPKG}")

if(USE_VCPKG)
	set(VCPKG_CMAKE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
	set(CMAKE_TOOLCHAIN_FILE ${VCPKG_CMAKE})
	message(CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE})
endif ()

project(cppdetector)
set(CMAKE_CXX_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES main.cpp)

#add_definitions(-DBUILD_STATIC)


#vcpkg begin
if(USE_VCPKG)
	message("option for USE_VCPKG...")
	add_definitions(-DVCPKG)
	find_package(unofficial-breakpad CONFIG REQUIRED)
	link_libraries(unofficial::breakpad::libbreakpad unofficial::breakpad::libbreakpad_client)
endif()
#vcpkg end

add_executable(cppdetector ${SOURCE_FILES})

include_directories(detector_core)
add_subdirectory(detector_core)
add_subdirectory(catch_tests)

if(USE_VCPKG)
message(create benchmark...)
add_subdirectory(catch_benchmarks)
endif()

target_link_libraries(cppdetector detector_core)