message(_HIBLUE_ "---Start---Configuring detector_core library:")

include(../3rdparty/3rdparty.cmake)
include(common/common.cmake)
include(detectorcommon/detectorcommon.cmake)
include(detectors/detectors.cmake)
include(detectorcontext/detectorcontext.cmake)

FILE(GLOB_RECURSE DETECTORS_CORE_H "*.h")
FILE(GLOB_RECURSE DETECTORS_CORE_CPP  "*.cpp")
SET(SOURCES
	${SOURCES}
	${DETECTORS_CORE_CPP}
)
SET(HEADERS
	${HEADERS}
	${DETECTORS_CORE_H}
)