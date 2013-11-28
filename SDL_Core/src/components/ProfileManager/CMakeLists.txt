# --- Utils
add_subdirectory(./ProfileManagerUtils)
add_subdirectory(./ApplicationManagerHmiProtocol)
# --- ProfileProcess
add_subdirectory(./ProfileProcess)

include_directories (
  ./include
  ./ProfileManagerUtils/include/
  ./ApplicationManagerHmiProtocol/include/
  ./../Utils/include/
  ./../Utils/ZmqUtils/include/
  ./../TransportManager/include/
  ./../JSONHandler/include/
  ./../../thirdPartyLibs/jsoncpp/include/
  ./../AppMgr/include/
  ./../../thirdPartyLibs/logger/include/
  ./../../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ./../../thirdPartyLibs/zeromq-3.2.3/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include
)

set (SOURCES
  ./src/ProfileCommunicator.cpp
  ./src/ProfileInstanceManager.cpp
  ./src/ProfileManager.cpp
  ./src/ActiveProfilesRegister.cpp
  ./src/ProfileConnectionsRegister.cpp
  ./src/ProfileLibrariesManager.cpp
  ./src/ApplicationManagerHmiCommunicator.cpp
)

set (HEADERS
  ./include/ProfileManager/IProfile.h
  ./include/ProfileManager/IProfileCallbacks.h
  ./include/ProfileManager/ProfileInstanceManager.h
  ./include/ProfileManager/ProfileManager.h
  ./include/ProfileManager/ProfileManagerCommon.h
  ./include/ProfileManager/ActiveProfilesRegister.h
  ./include/ProfileManager/ProfileConnectionsRegister.h
  ./include/ProfileManager/ProfileLibrariesManager.h
  ./include/ProfileManager/ProfileManagerResult.h
)

add_library("ProfileManager" ${SOURCES} ${HEADERS})
