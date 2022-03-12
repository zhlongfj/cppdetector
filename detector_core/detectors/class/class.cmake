﻿SET(DIR_NAME detectors/class)

FILE(GLOB_RECURSE RECURSE_H "./${DIR_NAME}/*.h*")
FILE(GLOB_RECURSE RECURSE_CPP  "./${DIR_NAME}/*.cpp")
FILE(GLOB_RECURSE RECURSE_CMAKE  "./${DIR_NAME}/*.cmake")
SOURCE_GROUP("${DIR_NAME}/Header Files" FILES ${RECURSE_H})
SOURCE_GROUP("${DIR_NAME}/Source Files" FILES ${RECURSE_CPP})
SOURCE_GROUP("${DIR_NAME}" FILES ${RECURSE_CMAKE})

SET(HEADERS
	${RECURSE_CMAKE}
)