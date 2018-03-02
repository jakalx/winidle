cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (META_PROJECT_NAME "winidle")

project(${META_PROJECT_NAME} C)

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
