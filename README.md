# winidle
`winidle` prints the idle time on Windows(R) and Linux systems in milliseconds.

## Build

Requires cmake and a C compiler.

### Linux (CMake)

Uses the Xscreensaver library to get the idle time.
```
mkdir build
cd build
cmake ..
make
```

Will create the executable `src/winidle`.

### Linux (manually)
```
gcc -o winidle src/winidle.c -lX11 -lXss
```

### Windows (cross-compilation)
```
mkdir build-w32
cd build-w32
cmake .. -DCMAKE_TOOLCHAIN_FILE=../Toolchain-mingw32.cmake
make
```

Will create the executable `src/winidle.exe`.

### Windows (native)

Use CMake to generate a Visual Studio project, open and build it. This part is currently untested.

## How to use it in org-mode
```lisp
(defun org-user-idle-seconds ()
  "Return the current Win idle time in seconds."
  (/ (string-to-number (shell-command-to-string "winidle.exe")) 1000))
```
