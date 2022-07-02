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
	MESSAGE(STATUS "Now is UNIX-like OS.")
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

#内嵌nanobench库
#include(FetchContent)
#FetchContent_Declare(
#    nanobench
#    GIT_REPOSITORY https://github.com/martinus/nanobench.git
#    GIT_TAG v4.1.0
#    GIT_SHALLOW TRUE)
#FetchContent_MakeAvailable(nanobench)

add_executable(cppdetector ${SOURCE_FILES})

set(REL_WITH_DEBINFO_PATH ${EXECUTABLE_OUTPUT_PATH}/RelWithDebInfo)
set(SUPPORTING_PATH ${PROJECT_SOURCE_DIR}/supporting)
IF (WIN32)
	MESSAGE(STATUS "copy file, Now is windows")
	set(RELEASE_PATH ${PROJECT_SOURCE_DIR}/release/windows_x64)
	add_custom_command(TARGET cppdetector POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${REL_WITH_DEBINFO_PATH} ${RELEASE_PATH}/cppdetector)
	add_custom_command(TARGET cppdetector POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${SUPPORTING_PATH}/exceptionconfig.json ${RELEASE_PATH}/config)
ELSEIF (APPLE)
	MESSAGE(STATUS "copy file, Now is Apple system.")
ELSEIF (UNIX)
	MESSAGE(STATUS "copy file, Now is UNIX-like OS.")
ENDIF ()

	
include_directories(detector_core)
add_subdirectory(detector_core)
add_subdirectory(unit_tests)

if(USE_VCPKG)
message(create benchmark...)
add_subdirectory(catch_benchmarks)
endif()

target_link_libraries(cppdetector detector_core)