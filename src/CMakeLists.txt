set (target winidle)
set (sources winidle.cpp)

if (UNIX)
  find_package(X11)
  if (NOT X11_Xscreensaver_FOUND)
    message(FATAL_ERROR "X11 Screensaver library (libXss) is required")
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

add_definitions(-DMETA_NAME_VERSION="${META_NAME_VERSION}")
add_executable (${target} ${sources})

if (UNIX)
  #  target_include_directories(${target} ${X11_INCLUDE_DIR})
  target_link_libraries(${target} ${X11_LIBRARIES} ${X11_Xscreensaver_LIB})
endif()

install (TARGETS ${target}
  RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT examples
)
