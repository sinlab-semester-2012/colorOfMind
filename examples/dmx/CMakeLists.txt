add_executable (dmx_demo dmx_demo.cpp)
ADD_DEPENDENCIES(dmx_demo emokit read_data emokit_dsp emotions ofxDmx)
target_link_libraries (dmx_demo emokit read_data emokit_dsp emotions ofxDmx ${LIBS})

SET_TARGET_PROPERTIES(dmx_demo PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS dmx_demo
	RUNTIME DESTINATION bin
)

