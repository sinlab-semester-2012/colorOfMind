##########################################
##              libepoc                ###
##########################################

# Create a library called "libepoc"
ADD_LIBRARY (emokit STATIC emokit.c) 
target_link_libraries (emokit ${LIBS}) 

INSTALL (TARGETS emokit
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${LIBEMOKIT_HEADERS}
  DESTINATION include/libemokit
  )
  
# Create a library called "save_data"
ADD_LIBRARY (save_data STATIC save_data.c) 
target_link_libraries (save_data emokit ${LIBS}) 

INSTALL (TARGETS save_data
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${SAVE_DATA_HEADERS}
  DESTINATION include/save_data_lib
  )


# Create a library called "read_data"
ADD_LIBRARY (read_data STATIC read_data.c) 
target_link_libraries (read_data emokit ${LIBS}) 

INSTALL (TARGETS read_data
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${READ_DATA_HEADERS}
  DESTINATION include/read_data_lib
  )
  
  
# Create a library called "GNUPLOT_I"
ADD_LIBRARY (gnuplot_i STATIC gnuplot_i.c) 
target_link_libraries (gnuplot_i ${LIBS}) 

INSTALL (TARGETS gnuplot_i
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${READ_DATA_HEADERS}
  DESTINATION include/gnuplot_i_lib
  )

  # Create a library called "classifier"
ADD_LIBRARY (classifier STATIC classifier.c) 
target_link_libraries (classifier emokit ${LIBS}) 

INSTALL (TARGETS classifier
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${CLASSIFIER_HEADERS}
  DESTINATION include/classifier_lib
  )


# Create a library called "emokit_dsp"
ADD_LIBRARY (emokit_dsp STATIC emokit_dsp.c) 
# link the math library for linux, automatic for windows
IF(UNIX)
  TARGET_LINK_LIBRARIES(emokit_dsp m)
ENDIF(UNIX)
  target_link_libraries(emokit_dsp emokit classifier ${LIBS})

INSTALL (TARGETS emokit_dsp
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${EMOKIT_DSP_HEADERS}
  DESTINATION include/emokit_dsp_lib
  )


# Create a library called "emotions"
ADD_LIBRARY (emotions STATIC emotions.c) 
# link the math library for linux, automatic for windows
IF(UNIX)
  TARGET_LINK_LIBRARIES(emotions m)
ENDIF(UNIX)
  target_link_libraries(emotions emokit emokit_dsp ${LIBS})


INSTALL (TARGETS emotions
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${EMOTIONS_HEADERS}
  DESTINATION include/emotions_lib
  )


# Create a library called "plot"
ADD_LIBRARY (plot STATIC plot.c) 
target_link_libraries (plot emokit emokit_dsp gnuplot_i ${LIBS}) 

INSTALL (TARGETS plot
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${PLOT_HEADERS}
  DESTINATION include/plot_lib
  )

