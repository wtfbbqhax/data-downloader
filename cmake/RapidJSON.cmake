include(ExternalProject)

set(RapidJSON_REPO "https://github.com/miloyip/rapidjson.git")
#set(RapidJSON_TAG "")

set(EP_BASE "external")

ExternalProject_Add(RapidJSON
    GIT_REPOSITORY  ${RapidJSON_REPO}
#    GIT_TAG         ${RapidJSON_TAG}
    GIT_SHALLOW     1
    INSTALL_DIR
    INSTALL_COMMAND
#    BUILD_DIR
    BUILD_COMMAND
    BUILD_IN_SOURCE 1
    TEST_COMMAND
    UPDATE_DISCONNECTED 1
    TEST_COMMAND

    )

ExternalProject_Get_Property(RapidJSON source_dir)
set(RapidJSON_SOURCE_DIR ${source_dir})
set(RapidJSON_INCLUDE_DIR ${RapidJSON_SOURCE_DIR}/include)
mark_as_advanced(RapidJSON_INCLUDE_DIR)

message(STATUS " RapidJSON_INCLUDE_DIR: ${RapidJSON_INCLUDE_DIR}")
