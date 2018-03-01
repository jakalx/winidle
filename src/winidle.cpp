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

#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

#if   defined(_WIN32)
#  include <SDKDDKVer.h>
#  include <Windows.h>
#elif defined(__linux__)
#  include <X11/Xlib.h>
#  include <X11/extensions/scrnsaver.h>
#else
#  error "Platform is not yet supported."
#endif

namespace util {
  std::chrono::milliseconds get_idle_time() {
#if defined(_WIN32)
    LASTINPUTINFO last_input_info;
    last_input_info.cbSize = sizeof(LASTINPUTINFO);
    if (GetLastInputInfo(&last_input_info)) {
      return std::chrono::milliseconds(GetTickCount64() - last_input_info.dwTime);
    } else {
      throw std::runtime_error
        ("GetLastInputInfo() failed: " + std::to_string(GetLastError()));
    }
#else
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) {
      throw std::runtime_error ("XOpenDisplay() failed");
    }

    XScreenSaverInfo info;
    if (! XScreenSaverQueryInfo (display, DefaultRootWindow (display), &info)) {
      XCloseDisplay (display);
      throw std::runtime_error ("XScreenSaverQueryInfo() failed");
    }

    XCloseDisplay (display); display = nullptr;

    return std::chrono::milliseconds (info.idle);
#endif

    assert(! "get_idle_time(): should not be reached!");
  }
}

int main(int argc, char * argv[]) {
  try {
    for (int i = 1; i < argc; ++i) {
      const std::string arg{ argv[i] };
      if (arg == "-h" || arg == "--help") {
        std::cout << "usage: " << argv[0] << " [-h|--help|-V|--version]" << std::endl;
        return 0;
      } else if (arg == "-V" || arg == "--version") {
        std::cerr << META_NAME_VERSION << std::endl;
        return 0;
      } else {
        std::cerr << "invalid option: " << arg << std::endl;
        return 1;
      }
    }

    std::cout << util::get_idle_time().count() << std::endl;
    return EXIT_SUCCESS;
  }
  catch (const std::exception& ex) {
    std::cerr << "E: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}
