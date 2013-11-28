include_directories (
  ./include
  ./../include/
  ./../../../thirdPartyLibs/logger/include/
  ./../../../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ./../../../thirdPartyLibs/zeromq-3.2.3/include/
  ./../../JSONHandler/include/
  ./../../Utils/include/
  ./../../../thirdPartyLibs/jsoncpp/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include
)

set (SOURCES
  ./src/ProfilesAppsMessage.cpp
)

set (HEADERS
  ./include/ApplicationManagerHmiProtocol/ProfilesAppsMessage.h
)

add_library("AppManHmiProtocol" ${SOURCES} ${HEADERS})
