##################################################
#                epoc daemon                   #
##################################################

add_executable (study study.c)
ADD_DEPENDENCIES(study emokit save_data)
target_link_libraries (study emokit save_data ${LIBS})

SET_TARGET_PROPERTIES(study PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS study
	RUNTIME DESTINATION bin
)

