cmake_minimum_required(VERSION 3.6)
project(GetUpdate) 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#include(RapidJSON)
set(RapidJSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/rapidjson)
add_subdirectory(restclient)
add_subdirectory(src)
