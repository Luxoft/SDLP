include_directories (
  ./include
  ../../thirdPartyLibs/logger/include/
  ../../thirdPartyLibs/logger/log4cplus-1.1.0/include/
  ../Utils/include/
  ../../thirdPartyLibs/jsoncpp/include/
  ${CMAKE_BINARY_DIR}/SDL_Core/src/thirdPartyLibs/logger/log4cplus-1.1.0/include
)

set (SOURCES
    ./src/SDeviceInfo.cpp
    ./src/IDeviceAdapter.cpp
    ./src/IDeviceAdapterListener.cpp
    ./src/IHandleGenerator.cpp
    ./src/ITransportManager.cpp
    ./src/CBluetoothAdapter.cpp
    ./src/CDeviceAdapter.cpp
    ./src/CTransportManager.cpp
    ./src/CTCPAdapter.cpp
    ./src/SInternalDeviceInfo.cpp
    ./src/ITransportManagerDeviceListener.cpp
    ./src/ITransportManagerDataListener.cpp
    ./src/CTCPAutoconnectAdapter.cpp
)

add_library("TransportManager" ${SOURCES})
