add_definitions(-std=c++11)
add_executable( get main.cc )
target_link_libraries( get RESTCLIENT )
target_link_libraries( get ${CURL_LIBRARIES} )
target_link_libraries( get cJSON )
include_directories(BEFORE ${CMAKE_SOURCE_DIR}) 

add_executable( autoupdate autoupdate.cpp )

