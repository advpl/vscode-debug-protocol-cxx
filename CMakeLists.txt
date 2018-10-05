cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 14)
enable_testing()
project(vscode-debug-protocol-lib)
if (WIN32)
    macro(get_WIN32_WINNT version)
        if (CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if ("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif ("${verMajor}" MATCHES "10")
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif(CMAKE_SYSTEM_VERSION)
    endmacro(get_WIN32_WINNT)

    ADD_DEFINITIONS(-DUNICODE)
    ADD_DEFINITIONS(-D_UNICODE)
    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
    #add_definitions(-D_WIN32_WINNT=0x0501)
    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
        add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    endif(MSVC)
endif(WIN32)

set(LIB_SOURCES
    src/DebugProtocolCallbacks.cpp
    src/DebugProtocolServer.cpp
    src/JSONOutput.cpp
    src/JSONRPCDispatcher.cpp
    src/Logger.cpp
    src/ProtocolHandlers.cpp
    src/Protocol.cpp
)

set(LIB_HEADERS
    include/DebugProtocolCallbacks.hpp
    include/DebugProtocolServer.hpp
    include/Handler.hpp
    include/json.hpp
    include/JSONOutput.hpp
    include/JSONRPCDispatcher.hpp
    include/Logger.hpp
    include/ProtocolHandlers.hpp
    include/Protocol.hpp
)

find_package(Threads)

# Boost
message("------------rodrigo-------------------------")
if (NOT DEFINED     BOOST_ROOT        AND
NOT DEFINED ENV{BOOST_ROOT}       AND
NOT DEFINED     BOOST_INCLUDEDIR  AND
NOT DEFINED ENV{BOOST_INCLUDEDIR} AND
NOT DEFINED     BOOST_LIBRARYDIR  AND
NOT DEFINED ENV{BOOST_LIBRARYDIR})
if (APPLE)
    message("------------apple-------------------------")
    set(BOOST_ROOT "/usr/local/boost_1_65_1/")
    set (BOOST_INCLUDEDIR "/usr/local/boost_1_65_1/boost/")
elseif (UNIX)
    set(BOOST_ROOT "/opt/boost")
    set (BOOST_INCLUDEDIR "/opt/boost/boost/")
    set (BOOST_LIBRARYDIR "/opt/boost/lib/")    
elseif (WIN32)
    set (BOOST_ROOT "C:/local/boost_1_68_0/" )
    set (BOOST_LIBRARYDIR "C:/local/boost_1_68_0/stage/VS/x64/lib/")
endif()
endif()
if(UNIX)
    set(BOOST_ROOT "/opt/boost")
    set (BOOST_INCLUDEDIR "/opt/boost/boost/")
    set (BOOST_LIBRARYDIR "/opt/boost/lib/")        
endif(UNIX)
ADD_DEFINITIONS("-std=c++11")

###############################################################################
## dependencies ###############################################################
###############################################################################

# this defines the variables Boost_LIBRARIES that contain all library names
# that we need to link to 

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)
set (Boost_NO_BOOST_CMAKE ON)
#set (Boost_DEBUG true)
find_package(Boost
        REQUIRED
        log_setup
        log
        filesystem
        system
        thread
        serialization
        date_time
        regex
        unit_test_framework
        program_options
        locale
        REQUIRED)

add_library( ${PROJECT_NAME} ${LIB_SOURCES} ${LIB_HEADERS} )
include_directories(${Boost_INCLUDE_DIRS})
include_directories( include/)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


#add_executable(testeDebug src/ZMain.cpp ${data} ${LIB_HEADERS})
#target_link_libraries(testeDebug
#  ${Boost_LIBRARIES}
#  ${PROJECT_NAME} 
#  ${CMAKE_THREAD_LIBS_INIT}
#)

# End Boost

add_subdirectory(test)