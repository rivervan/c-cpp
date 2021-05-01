cmake_minimum_required(VERSION 3.7)

#add_definitions(-std=c++17)
#set(CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")

project(ioFundamentals)



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_executable(ioFundamentals src/ioFundamentals.cpp )

