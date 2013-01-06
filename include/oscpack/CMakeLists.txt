cmake_minimum_required(VERSION 2.6)
PROJECT(OSC)

INCLUDE_DIRECTORIES(${OSC_SOURCE_DIR})


IF(WIN32)
set(SystemTypePath ip/win32)
ELSE(WIN32)
set(SystemTypePath ip/posix)
ENDIF(WIN32)

ADD_LIBRARY(oscpack

ip/IpEndpointName.cpp
${SystemTypePath}/NetworkingUtils.cpp
${SystemTypePath}/UdpSocket.cpp

osc/OscPrintReceivedElements.cpp
osc/OscReceivedElements.cpp
osc/OscTypes.cpp
osc/OscOutboundPacketStream.cpp
)

INSTALL (TARGETS oscpack
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )

INSTALL(FILES
  ${LIBEMOKIT_HEADERS}
  DESTINATION include/liboscpack
  )

