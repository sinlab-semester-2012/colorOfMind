add_executable (arduino arduino.c)
ADD_DEPENDENCIES(arduino emokit read_data emokit_dsp emotions)
target_link_libraries (arduino emokit read_data emokit_dsp emotions ${LIBS})

SET_TARGET_PROPERTIES(arduino PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS arduino
	RUNTIME DESTINATION bin
)

