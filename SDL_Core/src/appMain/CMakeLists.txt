set(LIBRARIES
  -Wl,--start-group
  AppMgr
  JSONHandler
  JSONHandlerV1
  JSONHandlerV2
  JSONHandlerRPC
  ProtocolHandler
  connectionHandler
  TransportManager
  MessageBroker
  MessageBrokerClient
  MessageBrokerServer
  ProfileManager
  ProfileManagerUtils
  AppManHmiProtocol
  Utils
  encryption
  jsoncpp
  bluetooth
  pthread
  log4cplus
  rt
  ZmqSocket
  zmq
  uuid
  -Wl,--end-group
)

include_directories (
  ./
  ../components/ProfileManager/include/
  ../components/ProtocolHandler/include/
  ../thirdPartyLibs/jsoncpp/include/
  ../components/JSONHandler/include/
  ../components/AppMgr/include
  ../components/TransportManager/include/
  ../components/Utils/include/
  ../components/ConnectionHandler/include/
  ../components/ProfileManager/include/
  ../thirdPartyLibs/MessageBroker/include/
  ../thirdPartyLibs/logger/include/
  ../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ../thirdPartyLibs/encryption/include/
  ../thirdPartyLibs/zeromq-3.2.3/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include/
)

set (SOURCES
  appMain.cpp
)

if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build. Options are: None, Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)
endif()

add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log4cplus.properties DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/audio.8bit.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/hmi_link "${CMAKE_HOME_DIRECTORY}/SDL_Core/src/components/HMI/index.html")
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/hmi_link DESTINATION ${PROJECT_BINARY_DIR}/bin/)
install (TARGETS ${PROJECT} DESTINATION bin)

