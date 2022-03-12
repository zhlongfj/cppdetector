#add_definitions(-DBUILD_STATIC)
INCLUDE(catch_tests.cmake)
add_executable(catch_tests_run ${SOURCES})
target_link_libraries(catch_tests_run detector_core)