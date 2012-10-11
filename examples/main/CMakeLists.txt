##################################################
#                main                  #
##################################################

# Make sure the compiler can find include files from our library.
include_directories (${band_waves_SOURCE_DIR}/band_waves)
# Make sure the linker can find the library once it is built.
link_directories (${band_waves_BINARY_DIR}/band_waves)
add_executable (main main.c)
# Link the executable to the librairies. 
target_link_libraries (main emokit band_waves ${LIBS})
