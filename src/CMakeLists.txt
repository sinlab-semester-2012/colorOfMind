
IF(WIN32)
  ADD_LIBRARY (emokit STATIC emokit.c emokit_win32.c)
ELSE()
  ADD_LIBRARY (emokit STATIC emokit.c emokit_libusb.c)
ENDIF()

ADD_LIBRARY (band_waves band_waves.c) 


