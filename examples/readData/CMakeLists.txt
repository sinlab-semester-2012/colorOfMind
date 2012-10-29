##################################################
#                readData                  #
##################################################

###BAND_WAWES
# Make sure the compiler can find include files from our library.
include_directories (${band_waves_SOURCE_DIR}/band_waves)
# Make sure the linker can find the library once it is built.
link_directories (${band_waves_BINARY_DIR}/band_waves)

### DATA_HEADSET
# Make sure the compiler can find include files from our library.
include_directories (${data_headset_SOURCE_DIR}/data_headset)
# Make sure the linker can find the library once it is built.
link_directories (${data_headset_BINARY_DIR}/data_headset)


add_executable (readData readData.c)
# Link the executable to the librairies. 
target_link_libraries (readData emokit band_waves data_headset ${LIBS})
