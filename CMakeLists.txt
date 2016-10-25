cmake_minimum_required(VERSION 3.6)
project(GetUpdate) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(RapidJSON)

add_subdirectory(restclient)
add_subdirectory(src)
