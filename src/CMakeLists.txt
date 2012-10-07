##########################################
##              libepoc                ###
##########################################

# Create a library called "libepoc"
IF(WIN32)
  ADD_LIBRARY (emokit STATIC emokit.c emokit_win32.c) 
ELSE()
  ADD_LIBRARY (emokit STATIC emokit.c emokit_libusb.c) 
ENDIF()
target_link_libraries (emokit ${LIBS}) 

INSTALL (TARGETS emokit
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${LIBEMOKIT_HEADERS}
  DESTINATION include/libemokit
  )

##########################################
##              libbw               ###
##########################################

# Create a library called "libbw"
ADD_LIBRARY (band_waves STATIC band_waves.c) 
target_link_libraries (band_waves ${LIBS}) 

INSTALL (TARGETS band_waves
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${LIBBAND_WAVES_HEADERS}
  DESTINATION include/band_waves
  )

##################################################
#                epoc daemon                   #
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

