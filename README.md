bomberman
=========

[![Build Status](https://travis-ci.org/Neki/bomberman.svg)](https://travis-ci.org/Neki/bomberman)
[![Coverity Scan Build](https://scan.coverity.com/projects/3081/badge.svg)](https://scan.coverity.com/projects/3081/badge.svg)

Yet another bomberman clone (student project - written in C++)

## Project structure

This project is composed of
* a Bomberman client that connects to a server
* a Bomberman server that runs the game
* a library containing code shared by both the client and the server

## Build

The project can be built using CMake. You need to have the Qt5 libraries installed on your system. Detailed instructions by operating system follow.

### Ubuntu

#### Install tools and dependencies

```
sudo apt-get update
sudo apt-get install cmake build-essential
sudo apt-get install qt5-default
```

#### Build the project with CMake

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

You can also use the `Debug` build type (includes debug symbols information, lower optimization settings...)

By default, this will also download the Google Test framework and compile the project test suite. Pass `-Denable_tests=OFF` to `cmake` to skip this step.

#### Run the tests

If you called CMake with the `-Denable_tests=ON` flag (set by default), then you can run the test suite with `make test`.

