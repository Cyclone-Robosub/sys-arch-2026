cmake_minimum_required(VERSION 3.8)
project(fd_interface)

include_directories(fd_interface PRIVATE include)
include_directories(fd_interface PRIVATE src)

add_library(fd_interface SHARED
    src/fd_interface.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})