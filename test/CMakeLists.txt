cmake_minimum_required(VERSION 3.0)

project(debug-protocol-test)

add_executable(${PROJECT_NAME} basic_protocol_test.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

#target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
add_test(NAME teste1 COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES})