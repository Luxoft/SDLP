include_directories (
  ../../thirdPartyLibs/jsoncpp/include/
  ./include
  ../../thirdPartyLibs/logger/include/
  ../../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include
)

set (SOURCES
    ./src/WorkWithOS.cpp
    ./src/Base64Coder.cpp
    ./src/UUID.cpp
)

add_library("Utils" ${SOURCES})
