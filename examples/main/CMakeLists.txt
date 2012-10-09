##################################################
#                main                  #
##################################################

add_executable (main main.c)
ADD_DEPENDENCIES(main emokit)
ADD_DEPENDENCIES(main band_waves)
target_link_libraries (main emokit band_waves ${LIBS})

SET_TARGET_PROPERTIES(main PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS main
	RUNTIME DESTINATION bin
)

