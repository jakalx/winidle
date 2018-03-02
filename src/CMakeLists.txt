set (target winidle)
set (sources winidle.c)

if (UNIX)
  find_package(X11)
  if (NOT X11_Xscreensaver_FOUND)
    message(FATAL_ERROR "X11 Screensaver library (libXss) is required")
  endif()
endif()

if (WIN32)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

add_executable (${target} ${sources})

if (UNIX)
  target_include_directories (${target} SYSTEM PRIVATE ${X11_INCLUDE_DIR})
  target_link_libraries (${target} ${X11_LIBRARIES} ${X11_Xscreensaver_LIB})
endif()

install (TARGETS ${target}
  RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT examples
)
