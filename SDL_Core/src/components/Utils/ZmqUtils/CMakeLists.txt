include_directories (
  ./include/
  ./../../../thirdPartyLibs/logger/include/
  ./../../../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include/
)

set (SOURCES
  ./src/ZmqSocket.cpp
  ./src/SenderZmqSocket.cpp
  ./src/ReceiverZmqSocket.cpp
  ./src/ZmqClient.cpp
  ./src/ZmqServer.cpp
  ./src/ZmqSocketsRegister.cpp
)

set (HEADERS
  ./include/ZmqSocket/ZmqSocket.h
  ./include/ZmqSocket/SenderZmqSocket.h
  ./include/ZmqSocket/ReceiverZmqSocket.h
  ./include/ZmqSocket/SocketConnectionType.h
  ./include/ZmqSocket/ZmqSocketCommon.h
  ./include/ZmqSocket/ZmqClient.h
  ./include/ZmqSocket/ZmqServer.h
  ./include/ZmqSocket/ZmqSocketsRegister.h
)

add_library("ZmqSocket" ${SOURCES} ${HEADERS})
