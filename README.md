bomberman
=========

[![Build Status](https://travis-ci.org/Neki/bomberman.svg)](https://travis-ci.org/Neki/bomberman)
[![Coverity Scan Build](https://scan.coverity.com/projects/3081/badge.svg)](https://scan.coverity.com/projects/3081/badge.svg)

Yet another bomberman clone (student project - written in C++)

## Build

The project can be built using CMake. You need to have the Qt5 libraries installed on your system. Detailed instructions by operating system follows.

### Ubuntu

*Install basic tools*

```
sudo apt-get update
sudo apt-get install cmake build-essential
```

*Install Qt5*

```
sudo apt-get install qt5-default
```

*Build the project with CMake*

```
mkdir build && cd build
cmake .. -Dbuild_tests=ON
make
```

*Run the tests*

If (as described above) you called CMake with the `-Dbuild_tests=ON` flag, then you can run the test suite with `make test`.

