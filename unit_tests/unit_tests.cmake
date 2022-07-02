message(_HIBLUE_ "---Start---Configuring catch_tests:")

include(detectors/detectors.cmake)
include(common/common.cmake)
include(detectorcommon/detectorcommon.cmake)
FILE(GLOB_RECURSE CATCH_TESTS_H "*.h")
FILE(GLOB_RECURSE CATCH_TESTS_CPP  "*.cpp")
SET(SOURCES
	${SOURCES}
	${CATCH_TESTS_CPP}
)
SET(HEADERS
	${HEADERS}
	${CATCH_TESTS_H}
)