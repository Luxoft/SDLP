# --- logger
# Disabling log4cplus tests
IF(NOT DEFINED SKIP_LOG4CPLUS)
    option(LOG4CPLUS_BUILD_TESTING "Build log4cplus tests" OFF)
endif()

add_subdirectory(./logger/log4cplus-1.1.0)

# --- jsoncpp
add_subdirectory(./jsoncpp)

# --- MessageBroker
add_subdirectory(./MessageBroker)

# --- encryption
add_subdirectory(./encryption)
