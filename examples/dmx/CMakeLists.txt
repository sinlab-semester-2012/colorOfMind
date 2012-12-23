add_executable (dmx dmx.c)
ADD_DEPENDENCIES(dmx emokit read_data emokit_dsp emotions)
target_link_libraries (dmx emokit read_data emokit_dsp emotions ${LIBS})

SET_TARGET_PROPERTIES(dmx PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS dmx
	RUNTIME DESTINATION bin
)

