
IF(WIN32)
  ADD_LIBRARY (emokit STATIC emokit.c emokit_win32.c)
ELSE()
  ADD_LIBRARY (emokit STATIC emokit.c emokit_libusb.c)
ENDIF()

ADD_LIBRARY (band_waves band_waves.c) 
ADD_LIBRARY (data_headset STATIC data_headset.c)
ADD_LIBRARY (classifier classifier.c)

INSTALL (TARGETS emokit
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
  
 INSTALL (TARGETS data_headset
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )


