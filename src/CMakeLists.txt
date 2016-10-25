add_definitions(-std=c++14)
add_executable( get main.cc )

target_link_libraries( get RESTCLIENT )
include_directories( BEFORE
    ${CMAKE_SOURCE_DIR}
    ${RapidJSON_INCLUDE_DIR} )

add_dependencies(get RapidJSON)
add_dependencies(get RESTCLIENT)
