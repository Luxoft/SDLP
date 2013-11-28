set(LIBRARIES
  -Wl,--start-group
  log4cplus
  dl
  ProfileManagerUtils
  AppManHmiProtocol
  JSONHandler
  JSONHandlerV1
  JSONHandlerV2
  jsoncpp
  ZmqSocket
  zmq
  Utils
  -Wl,--end-group
)

include_directories (
  ./include
  ./../include/
  ./../ProfileManagerUtils/include/
  ./../ApplicationManagerHmiProtocol/include/
  ./../../Utils/include/
  ./../../Utils/ZmqUtils/include/
  ./../../TransportManager/include/
  ./../../../thirdPartyLibs/logger/include/
  ./../../../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ./../../../thirdPartyLibs/zeromq-3.2.3/include/
  ./../../JSONHandler/include/
  ./../../../thirdPartyLibs/jsoncpp/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include
)

set (SOURCES
  ./src/ProfileProcess.cpp
  ./src/ProfileManagerCommunicator.cpp
  ./src/main.cpp
)

set (HEADERS
  ./include/ProfileProcess/ProfileProcess.h
  ./include/ProfileProcess/ProfileManagerCommunicator.h
)

SET(MY_LIB_LINK_LIBRARIES -Wl,--whole-archive ProfileManagerUtils -Wl,--no-whole-archive)

add_executable("ProfileProcess" ${SOURCES} ${HEADERS})
target_link_libraries("ProfileProcess" ${MY_LIB_LINK_LIBRARIES})
target_link_libraries("ProfileProcess" ${LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/log4cplus.properties DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(WRITE ${CMAKE_BINARY_DIR}/bin/profile_process_link "${CMAKE_BINARY_DIR}/bin/ProfileProcess")
file(WRITE ${CMAKE_BINARY_DIR}/SDL_Core/src/appMain/profile_process_link "${CMAKE_CURRENT_BINARY_DIR}/ProfileProcess")
install (TARGETS ProfileProcess DESTINATION bin)
