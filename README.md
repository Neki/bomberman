bomberman
=========

[![Build Status](https://travis-ci.org/Neki/bomberman.svg?branch=master)](https://travis-ci.org/Neki/bomberman)
[![Coverity Scan Build](https://scan.coverity.com/projects/3081/badge.svg)](https://scan.coverity.com/projects/3081)

Yet another bomberman clone (student project - written in C++)

## Project structure

This project is composed of
* a Bomberman client that connects to a server
* a Bomberman server that runs the game
* a library containing code shared by both the client and the server

## Build

The project can be built using CMake (version 3.0.2 minimum). You need to have the Qt5 libraries installed on your system. Detailed instructions by operating system follow.

### Useful CMake options

* `cmake -Denable_tests=OFF` : disable tests (the unit tests will not be compiled nor run)
* `cmake -Dno_download=ON` : disable fetching external dependencies (easyloggingcpp and Google Test) from the Internet during compilation. You will need to have downloaded these dependencies into the appropriate folders (`build/gtest/src/googletest` and `build/easylogging/src/easyloggingcpp`) before starting the build.

### Windows 8

#### Install tools and dependencies

* Install Microsoft Visual Studio
* Install CMake (version 3.0.2 or greater) http://www.cmake.org/download/
* Install Qt (version 5.2 or greater) http://www.qt.io/download/
* Install tortoisesvn http://tortoisesvn.net/ (tick the command tools during the install)

#### Generate the Visual Studio project with CMake

Launch `C:\Program Files (x86)\CMake 3.0\bin\cmake-gui.exe`

Type in the source code path.

Type in the target directory path.

Add the following entry:
* Name: `CMAKE_PREFIX_PATH`; Type: `path`; Value: `C:/Qt/5.3/msvc2013_64/lib/cmake`

You can also set other options to configure your build (see the section `Useful CMake options`).

Click on 'Configure' => Choose your version of Visual Studio and do not change the others parameters.

Click on 'Generate'.

You now have a `.sln` file that can be used in Visual Studio. Use Visual Studio to build the projects (no further configuration *should* be needed).

After building the solution, you'll have 3 executables in your `bin/Debug` or `bin/Release` folder. If some QT DLLs are missing when you execute these .exe files, you should modify your PATH environment variable and add this path to the others: `C:\Qt\5.3\msvc2013_64\bin`. Then the executables should work.

#### Run the tests

You will find the test executables in the `bin/Debug`or `bin/Release` folder.

### Ubuntu

#### Install tools and dependencies

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install qt5-default
```

Install CMake (minimum version 3.0.2) following the instructions at http://www.cmake.org/download/.

#### Build the project with CMake and make

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

You can also use the `Debug` build type (includes debug symbols information, lower optimization settings...)

#### Run the tests

If you called CMake with the `-Denable_tests=ON` flag (set by default), then you can run the test suite with `make test`.

