##################################################
#                epoc daemon                   #
##################################################

add_executable (saveDataToFile saveDataToFile.c)
ADD_DEPENDENCIES(saveDataToFile emokit save_data)
target_link_libraries (saveDataToFile emokit save_data ${LIBS})

SET_TARGET_PROPERTIES(emokitd PROPERTIES
	INSTALL_RPATH_USE_LINK_PATH TRUE
	INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
	BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS saveDataToFile
	RUNTIME DESTINATION bin
)

