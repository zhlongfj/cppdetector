#add_definitions(-DBUILD_STATIC)
INCLUDE(unit_tests.cmake)
add_executable(unit_tests_run ${SOURCES})
target_link_libraries(unit_tests_run detector_core)