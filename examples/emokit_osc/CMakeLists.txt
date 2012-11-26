LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

#INCLUDE_DIRECTORIES(${oscpack_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
ADD_EXECUTABLE(emokit_osc emokit_osc.cpp)
ADD_DEPENDENCIES(emokit_osc epoc)
#TARGET_LINK_LIBRARIES(emokit_osc ${oscpack_LIBS} epoc ${LIBS})
TARGET_LINK_LIBRARIES(emokit_osc OSC emokit ${LIBS})

SET_TARGET_PROPERTIES(emokit_osc PROPERTIES
INSTALL_RPATH_USE_LINK_PATH TRUE
INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
BUILD_WITH_INSTALL_RPATH TRUE )

INSTALL (TARGETS emokit_osc
RUNTIME DESTINATION bin
)

##########################################
## EMOKIT OSC #
##########################################

#### DATA_HEADSET
## Make sure the compiler can find include files from our library.
#include_directories (${data_headset_SOURCE_DIR}/data_headset)
## Make sure the linker can find the library once it is built.
#link_directories (${data_headset_BINARY_DIR}/data_headset)


####BAND_WAWES
## Make sure the compiler can find include files from our library.
#include_directories (${emo_dsp_SOURCE_DIR}/emo_dsp)
## Make sure the linker can find the library once it is built.
#link_directories (${emo_dsp_BINARY_DIR}/emo_dsp)


#ADD_EXECUTABLE(emokit_osc emokit_osc.cpp)
#ADD_DEPENDENCIES(emokit_osc emokit)
#TARGET_LINK_LIBRARIES(emokit_osc emokit emo_dsp OSC data_headset ${LIBS})
#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

#SET_TARGET_PROPERTIES(emokit_osc PROPERTIES
#INSTALL_RPATH_USE_LINK_PATH TRUE
#INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib
#BUILD_WITH_INSTALL_RPATH TRUE )

#INSTALL (TARGETS emokit_osc
#RUNTIME DESTINATION bin
#)

