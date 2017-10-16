cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
enable_testing()
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
ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)

endif(WIN32)


project(vscode-debug-protocol)
set (Boost_DEBUG true)

if (NOT DEFINED     BOOST_ROOT        AND
NOT DEFINED ENV{BOOST_ROOT}       AND
NOT DEFINED     BOOST_INCLUDEDIR  AND
NOT DEFINED ENV{BOOST_INCLUDEDIR} AND
NOT DEFINED     BOOST_LIBRARYDIR  AND
NOT DEFINED ENV{BOOST_LIBRARYDIR})
if (APPLE)
    set(BOOST_ROOT "../../../boost/boost_1_54_0/mac")
elseif (UNIX)
    set(BOOST_ROOT "/home/rodrigo/dev/boost/")
    set (BOOST_INCLUDEDIR "/home/rodrigo/dev/boost/")
    set (BOOST_LIBRARYDIR "/home/rodrigo/dev/boost/stage/lib/")
    ADD_DEFINITIONS("-std=c++11")
elseif (WIN32)
    set (BOOST_ROOT "C:/local/boost_1_64_0" )
    set (BOOST_INCLUDEDIR "C:/local/boost_1_64_0" )
    set (BOOST_LIBRARYDIR "C:/local/boost_1_64_0/lib64-msvc-14.1")
endif()
endif()



#set(SOURCE hello.cpp)
set (Boost_NO_BOOST_CMAKE ON)
#file(GLOB_RECURSE sources      src/*.cpp include/connect/*.h)
file(GLOB_RECURSE sources      src/*.cpp)

#add_executable(${PROJECT_NAME} ${SOURCE})

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

find_package(Boost REQUIRED system thread serialization date_time regex  unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${sources} ${data})

target_link_libraries(${PROJECT_NAME} 
  ${Boost_LIBRARIES}
  # here you can add any library dependencies
)
add_subdirectory(test)