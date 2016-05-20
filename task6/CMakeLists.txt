cmake_minimum_required(VERSION 3.3)
project(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(. ${SOURCE_FILES})
add_library(lazy_string lazy_string.cpp)

target_link_libraries(. lazy_string)

install(TARGETS lazy_string DESTINATION lib)
install(FILES lazy_string.h DESTINATION include)