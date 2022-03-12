project(detector_core)
#add_definitions(-DBUILD_STATIC)
add_definitions(-DDETECTOR_LIB)

SET(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/../bin)

set(HEADER_FILES)

set(SOURCE_FILES)

INCLUDE(detector_core.cmake)

#add_library(detector_core STATIC ${SOURCES} ${HEADERS})
add_library(detector_core SHARED ${SOURCES} ${HEADERS})
