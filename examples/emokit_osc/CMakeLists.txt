#########################################
# EMOKIT OSC #
#########################################

### DATA_HEADSET
# Make sure the compiler can find include files from our library.
include_directories (${data_headset_SOURCE_DIR}/data_headset)
# Make sure the linker can find the library once it is built.
link_directories (${data_headset_BINARY_DIR}/data_headset)

ADD_EXECUTABLE(emokit_osc emokit_osc.cpp)
TARGET_LINK_LIBRARIES(emokit_osc emokit ${LIBS} OSC data_headset)

SET_TARGET_PROPERTIES(emokit_osc PROPERTIES
INSTALL_RPATH_USE_LINK_PATH TRUE
INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/include
BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS emokit_osc
RUNTIME DESTINATION bin
)

