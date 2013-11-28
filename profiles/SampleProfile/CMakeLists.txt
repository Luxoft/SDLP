include_directories (
  ./include
  ../../SDL_Core/src/components/Utils/include/
  ../../SDL_Core/src/components/JSONHandler/include/
  ../../SDL_Core/src/components/ProfileManager/include/
  ../../SDL_Core/src/components/ProfileManager/ProfileManagerUtils/include/
  ../../SDL_Core/src/thirdPartyLibs/jsoncpp/include/
  ../../SDL_Core/src/thirdPartyLibs/logger/include/
  ../../SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include
)

set (SOURCES
  ./src/SampleProfile.cpp
)

set (HEADERS
  ./include/SampleProfile/SampleProfile.h
)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL_Android/SmartDeviceLinkTester/assets/")

add_library("SampleProfile" SHARED ${SOURCES} ${HEADERS})

install(TARGETS SampleProfile LIBRARY DESTINATION lib/profiles/
                          ARCHIVE DESTINATION lib/profiles/
                          RUNTIME DESTINATION bin)
