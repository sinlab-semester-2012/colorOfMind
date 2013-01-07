##################################################
#                epoc daemon                   #
##################################################

add_executable (readData readData.c)
ADD_DEPENDENCIES(readData emokit read_data emokit_dsp plot emotions)
target_link_libraries (readData emokit read_data emokit_dsp plot emotions ${LIBS})

SET_TARGET_PROPERTIES(readData PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS readData
	RUNTIME DESTINATION bin
)

