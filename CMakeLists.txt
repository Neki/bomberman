cmake_minimum_required(VERSION 3.0.2)
project(bomberman)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

# Build options
option(enable_tests "Build tests" ON)
set(CMAKE_BUILD_TYPE Debug)

# Compiler options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Werror -Wextra -g -O0 -Wfloat-equal -pedantic -fPIE")
  set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Werror -Wextra -O3 -Wfloat-equal -pedantic -fPIE")
endif()

# Gather source files
file(GLOB_RECURSE SERVER_SRCS "src/server/*.cc")
file(GLOB_RECURSE CLIENT_SRCS "src/client/*.cc")
file(GLOB_RECURSE COMMON_SRCS "src/common/*.cc")
file(GLOB_RECURSE SERVER_TESTS_SRCS "tests/server/*.cc")
file(GLOB_RECURSE CLIENT_TESTS_SRCS "tests/client/*.cc")
file(GLOB_RECURSE COMMON_TESTS_SRCS "tests/common/*.cc")

# Tests
if(enable_tests)
  enable_testing()

  # Required for fetching and installing GTest
  include(ExternalProject)
  find_package(Threads)
  if(NOT ${Threads_FOUND})
    message(WARNING "Your platform does not provide a thread library supported by GTest. GTest will not be thread safe.")
  endif()

	set(GTEST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest")
	ExternalProject_Add(googletest
	    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
	    SVN_REVISION -r692
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

  # Ignore warnings from Google Test
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-isystem ${source_dir}/include -isystem ${source_dir}/src ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "-isystem ${source_dir}/include -isystem ${source_dir}/src ${CMAKE_CXX_FLAGS_RELEASE}")
  endif()

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
  add_test(runLibraryTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/runLibraryTests)

endif(enable_tests)

add_library(common ${COMMON_SRCS})
target_link_libraries(common Qt5::Core)

add_executable(bomberman ${CLIENT_SRCS})
target_link_libraries(bomberman Qt5::Widgets)
target_link_libraries(bomberman Qt5::Network)
target_link_libraries(bomberman common)

add_executable(bombServer ${SERVER_SRCS})
target_link_libraries(bombServer Qt5::Core)
target_link_libraries(bombServer Qt5::Network)
target_link_libraries(bomberman common)
