cmake_minimum_required(VERSION 3.0.2)
project(bomberman)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Qt
find_package(Qt5Core 5.2 REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Svg REQUIRED)

# Build options
option(enable_tests "Build tests" ON)
option(no_download "Prevent any download during the build process" OFF)
set(CMAKE_BUILD_TYPE Debug)

# Compiler options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "-Wnon-virtual-dtor -Wall -Werror -Wextra -Wno-reorder -g -O0 -Wfloat-equal -pedantic -fPIE -std=c++11")
  set(CMAKE_CXX_FLAGS_RELEASE "-Wnon-virtual-dtor -Wall -Werror -Wextra -Wno-reorder -O3 -Wfloat-equal -pedantic -fPIE -std=c++11")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "/W3 /Od /DNOMINMAX /MTd")
  set(CMAKE_CXX_FLAGS_RELEASE "/W3 /O2 /DNOMINMAX /MT")
endif()

# Gather source files
file(GLOB_RECURSE SERVER_SRCS "src/server/*.cc")
file(GLOB_RECURSE CLIENT_SRCS "src/client/*.cc")
file(GLOB_RECURSE COMMON_SRCS "src/common/*.cc")
file(GLOB_RECURSE SERVER_TESTS_SRCS "tests/server/*.cc")
file(GLOB_RECURSE CLIENT_TESTS_SRCS "tests/client/*.cc")
file(GLOB_RECURSE COMMON_TESTS_SRCS "tests/common/*.cc")

# Gather header files
file(GLOB_RECURSE SERVER_HEADERS "src/server/*.h")
file(GLOB_RECURSE CLIENT_HEADERS "src/client/*.h")
file(GLOB_RECURSE COMMON_HEADERS "src/common/*.h")
file(GLOB_RECURSE SERVER_TESTS_HEADERS "tests/server/*.h")
file(GLOB_RECURSE CLIENT_TESTS_HEADERS "tests/client/*.h")
file(GLOB_RECURSE COMMON_TESTS_HEADERS "tests/common/*.h")

# EasyLoggingCpp
include(easyloggingcpp.cmake)

# Tests
if(enable_tests)
  enable_testing()
  include(googletest.cmake)

  # Client tests
  add_executable(runClientTests ${CLIENT_TESTS_SRCS})
  target_link_libraries(runClientTests GTestMain)
  add_test(runClientTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/runClientTests)

  # Server tests
  add_executable(runServerTests ${SERVER_TESTS_SRCS})
  target_link_libraries(runServerTests GTestMain)
  add_test(runServerTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/runServerTests)

  # Common library tests
  add_executable(runLibraryTests ${COMMON_TESTS_SRCS})
  target_link_libraries(runLibraryTests GTestMain)
  target_link_libraries(runLibraryTests Qt5::Network)
  target_link_libraries(runLibraryTests common)
  add_test(runLibraryTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/runLibraryTests)

endif(enable_tests)

add_library(common ${COMMON_SRCS} ${COMMON_HEADERS})
target_link_libraries(common Qt5::Core)
add_dependencies(common easyloggingcpp)

add_executable(bomberman ${CLIENT_SRCS} ${CLIENT_HEADERS})
target_link_libraries(bomberman Qt5::Core)
target_link_libraries(bomberman Qt5::Widgets)
target_link_libraries(bomberman Qt5::Network)
target_link_libraries(bomberman Qt5::Svg)
target_link_libraries(bomberman common)
add_dependencies(bomberman easyloggingcpp)

add_executable(bombServer ${SERVER_SRCS} ${SERVER_HEADERS})
target_link_libraries(bombServer Qt5::Core)
target_link_libraries(bombServer Qt5::Widgets)
target_link_libraries(bombServer Qt5::Network)
target_link_libraries(bombServer common)
add_dependencies(bombServer easyloggingcpp)
