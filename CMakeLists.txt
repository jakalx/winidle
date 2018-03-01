cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (META_PROJECT_NAME "winidle")
set (META_VERSION_MAJOR "0")
set (META_VERSION_MINOR "1")
set (META_VERSION_PATCH "0")
set (META_VERSION       "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set (META_NAME_VERSION  "${META_PROJECT_NAME} v${META_VERSION}")

project(${META_PROJECT_NAME} CXX)

set (SYSTEM_DIR_INSTALL FALSE)
if ("${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr" OR "${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr/local")
    set(SYSTEM_DIR_INSTALL TRUE)
endif()

set (project ${META_PROJECT_NAME})
# Installation paths
if(UNIX AND SYSTEM_DIR_INSTALL)
    # Install into the system (/usr/bin or /usr/local/bin)
    set(INSTALL_ROOT      "share/${project}")       # /usr/[local]/share/<project>
    set(INSTALL_BIN       "bin")                    # /usr/[local]/bin
else()
    # Install into local directory
    set(INSTALL_ROOT      ".")                      # ./
    set(INSTALL_BIN       "bin")                    # ./bin
endif()

add_subdirectory(src)

install(FILES LICENSE DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
