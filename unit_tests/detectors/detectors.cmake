SET(DIR_NAME detectors)

include(detectors/dynamic/dynamic.cmake)
include(detectors/array/array.cmake)
include(detectors/confused/confused.cmake)
include(detectors/iterator/iterator.cmake)
include(detectors/lambda/lambda.cmake)
include(detectors/logic/logic.cmake)
include(detectors/loop/loop.cmake)
include(detectors/memleak/memleak.cmake)
include(detectors/operation/operation.cmake)
include(detectors/pointer/pointer.cmake)
include(detectors/singleton/singleton.cmake)
include(detectors/sizeof/sizeof.cmake)
include(detectors/uninit/uninit.cmake)
include(detectors/variable/variable.cmake)
include(detectors/inline/inline.cmake)
include(detectors/accesscontrol/accesscontrol.cmake)
include(detectors/class/class.cmake)

FILE(GLOB_RECURSE RECURSE_H "./${DIR_NAME}/*.h*")
FILE(GLOB_RECURSE RECURSE_CPP  "./${DIR_NAME}/*.cpp")
SOURCE_GROUP("${DIR_NAME}" FILES ${RECURSE_H} ${RECURSE_CPP})
SET(SOURCES
	${SOURCES}
	${RECURSE_H}
)
SET(HEADERS
	${HEADERS}
	${RECURSE_CPP}
)