// ***********************************************************************
//
// winidle.cpp --- outputs the user's idle-time in milliseconds
//
// Copyright (C) 2018 Alexander Kobjolke <alex@jakalx.net>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ***********************************************************************
//
// Aims to be platform independent.
//

#if ! defined(META_NAME_VERSION)
#  define META_NAME_VERSION "winidle 0.1.0"
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if   defined(_WIN32)
#  if ! defined(_WIN32_WINNT)
#    define _WIN32_WINNT 0x0600
#  endif
#
#  include <windows.h>
#elif defined(__linux__)
#  include <X11/Xlib.h>
#  include <X11/extensions/scrnsaver.h>
#else
#  error "Platform is not yet supported."
#endif

static unsigned long get_idle_time();

int main(int argc, char * argv[]) {
  int i;
  unsigned long idle_since;

  for (i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-h") == 0 || strcmp (argv[i], "--help") == 0) {
      printf ("usage: %s [-h|--help|-V|--version]\n", argv[0]);
      return 0;
    } else if (strcmp(argv[i], "-V") == 0 || strcmp (argv[i], "--version") == 0) {
      printf ("%s\n", META_NAME_VERSION);
      return 0;
    } else {
      fprintf (stderr, "invalid option: %s\n", argv[i]);
      return 1;
    }
  }

  idle_since = get_idle_time();
  if (idle_since == (unsigned long)-1) {
    return EXIT_FAILURE;
  }

  printf ("%lu\n", idle_since);
  return EXIT_SUCCESS;
}

unsigned long get_idle_time() {
#if defined(_WIN32)
  LASTINPUTINFO last_input_info;
  last_input_info.cbSize = sizeof(LASTINPUTINFO);
  if (! GetLastInputInfo(&last_input_info)) {
    fprintf(stderr, "GetLastInputInfo() failed");
    return (unsigned long)-1;
  }

  return (GetTickCount64() - last_input_info.dwTime);
#else
  Display *display;
  XScreenSaverInfo info;

  display = XOpenDisplay((char*)0);
  if (! display) {
    fprintf(stderr, "XOpenDisplay() failed");
    return (unsigned long)-1;
  }

  if (! XScreenSaverQueryInfo (display, DefaultRootWindow (display), &info)) {
    XCloseDisplay (display);
    fprintf(stderr, "XScreenSaveQueryInfo() failed");
    return (unsigned long)-1;
  }

  XCloseDisplay (display); display = 0;

  return info.idle;
#endif

  assert(! "get_idle_time(): should not be reached!");
}
