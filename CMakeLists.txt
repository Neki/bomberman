cmake_minimum_required(VERSION 2.8.11)
project(bomberman)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Required for fetching and installing GTest
include(ExternalProject)
find_package(Threads REQUIRED)

# Qt
find_package(Qt5Widgets REQUIRED)

# Build options
option(build_tests "Build tests" OFF)

# Compiler options
set(CMAKE_CXX_FLAGS "-g -Wall -Werror")

# Tests
if(build_tests)
  enable_testing()

	set(GTEST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest")
	ExternalProject_Add(googletest
	    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
	    SVN_REVISION -r HEAD
	    TIMEOUT 10
	    PREFIX "${GTEST_PREFIX}"
	    INSTALL_COMMAND ""
	    LOG_DOWNLOAD ON
	    LOG_CONFIGURE ON
	    LOG_BUILD ON)

  set(LIBPREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}")
  set(LIBSUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")
  set(GTEST_LOCATION "${GTEST_PREFIX}/src/googletest-build")
  set(GTEST_LIBRARY  "${GTEST_LOCATION}/${LIBPREFIX}gtest${LIBSUFFIX}")
  set(GTEST_MAINLIB  "${GTEST_LOCATION}/${LIBPREFIX}gtest_main${LIBSUFFIX}")

  add_library(GTest IMPORTED STATIC GLOBAL)
  set_target_properties(GTest PROPERTIES
    "IMPORTED_LOCATION" "${GTEST_LIBRARY}"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")

  add_library(GTestMain IMPORTED STATIC GLOBAL)
  set_target_properties(GTestMain PROPERTIES
    "IMPORTED_LOCATION" "${GTEST_MAINLIB}"
    "IMPORTED_LINK_INTERFACE_LIBRARIES"
    "${GTEST_LIBRARY};${CMAKE_THREAD_LIBS_INIT}")

  add_dependencies(GTest googletest)

  ExternalProject_Get_Property(googletest source_dir)
  include_directories(${source_dir}/include)

  add_executable(runTests tests/main_test.cpp)
  target_link_libraries(runTests GTestMain)
  add_test(runTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/runTests)
endif(build_tests)

add_executable(bomberman src/main.cpp)
target_link_libraries(bomberman Qt5::Widgets)
