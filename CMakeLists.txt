cmake_minimum_required(VERSION 2.8)

set (PROJECT smartDeviceLinkCore)
project (${PROJECT})

# Please do not change compiler/linker flags if You do not know how particular
# flag is handled by CMake
set(CMAKE_INSTALL_PREFIX .)
set(ARCHIVE_OUTPUT_DIRECTORY ./bin)
set(CMAKE_CXX_FLAGS "-g3 -ggdb3 -std=gnu++0x -Werror=return-type -Wuninitialized -fpermissive")
set(CMAKE_CXX_FLAGS_RELEASE "-s") #It will be appended to CMAKE_CXX_FLAGS in release

option( BUILD_SHARED_LIBS "Build all libraries as shared (if ON) or static (if OFF)" OFF)

# Building application

# --- ThirdPartyLibs
add_subdirectory(./SDL_Core/src/thirdPartyLibs)

# --- Components
add_subdirectory(./SDL_Core/src/components)

# --- Main application
add_subdirectory(./SDL_Core/src/appMain)

# --- Profiles
add_subdirectory(./profiles)

# Building tests
option(BUILD_TESTS "Possibility to build and run tests" OFF)
if(BUILD_TESTS)
    enable_testing()    
    # Framework GoogleTest is also integrated together gmock
    # and must not be added separately
    add_subdirectory(./SDL_Core/src/thirdPartyLibs/gmock-1.6.0)
    add_subdirectory(./test)
endif()


# Building documentation

# At first creating directory for generated documentation. Unfortunately doxygen
# cannot generate it byself
FIND_PACKAGE(Doxygen)
  IF(DOXYGEN_FOUND)
    option(DOXYGEN_ENABLE_DIAGRAMS "Enable graphical diagram generation" ON)
        
    if(DOXYGEN_ENABLE_DIAGRAMS)
      set(DOXYGEN_ENABLE_DIAGRAMS_PARAM "YES")
    else(DOXYGEN_ENABLE_DIAGRAMS)
      set(DOXYGEN_ENABLE_DIAGRAMS_PARAM "NO")
    endif()
    configure_file("${PROJECT_SOURCE_DIR}/SDL_Core/Doxyfile" "${PROJECT_BINARY_DIR}/Doxyfile")
    file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/doc/doxygen")
    ADD_CUSTOM_TARGET(doxygen COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_BINARY_DIR}/Doxyfile")
  ELSE(DOXYGEN_FOUND)
    MESSAGE(STATUS "Doxygen not found. Documentation will not be generated")
    MESSAGE(STATUS "To enable documentation generation please install doxygen and graphviz packages")
    MESSAGE(STATUS "sudo apt-get install doxygen graphviz")
    MESSAGE(STATUS "To enable processing of MscGen comments please install mscgen")
    MESSAGE(STATUS "sudo apt-get install mscgen")
ENDIF(DOXYGEN_FOUND)
 
