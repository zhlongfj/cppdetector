﻿SET(DIR_NAME detectors/dynamic)

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