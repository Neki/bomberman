# Define the GTest and GTestMain targets, to be linked against in tests.

include(ExternalProject)
find_package(Threads)
if(NOT ${Threads_FOUND})
  message(WARNING "Your platform does not provide a thread library supported by GTest. GTest will not be thread safe.")
endif()

set(GTEST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest")
set(LIBPREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}")
set(LIBSUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(GTEST_LOCATION "${GTEST_PREFIX}/src/googletest-build")
# And now, a ugly hack for your reading displeasure
# On Windows, the compiled Google shared lib is by default in a Debug (or Release) subdirectory.
# For some reason, GTest does not seem to respect the -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=... option
# and I have run out of ideas about how to do this cleanly
# So here is the brute-force solution:
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(GTEST_LIBRARY  "${GTEST_LOCATION}/${CMAKE_BUILD_TYPE}/${LIBPREFIX}gtest${LIBSUFFIX}")
  set(GTEST_MAINLIB  "${GTEST_LOCATION}/${CMAKE_BUILD_TYPE}/${LIBPREFIX}gtest_main${LIBSUFFIX}")
else()
  set(GTEST_LIBRARY  "${GTEST_LOCATION}/${LIBPREFIX}gtest${LIBSUFFIX}")
  set(GTEST_MAINLIB  "${GTEST_LOCATION}/${LIBPREFIX}gtest_main${LIBSUFFIX}")
endif()

if(NOT no_download)
  ExternalProject_Add(googletest
      SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk
      SVN_REVISION -r692
      TIMEOUT 10
      PREFIX "${GTEST_PREFIX}"
      INSTALL_COMMAND ""
      LOG_DOWNLOAD ON
      LOG_CONFIGURE ON
      LOG_BUILD ON)
else()
  ExternalProject_Add(googletest
      PREFIX "${GTEST_PREFIX}"
      INSTALL_COMMAND ""
      LOG_CONFIGURE ON
      LOG_BUILD ON)
endif()

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
add_dependencies(GTestMain googletest)

ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

# Ignore warnings from Google Test
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "-isystem ${source_dir}/include -isystem ${source_dir}/src ${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "-isystem ${source_dir}/include -isystem ${source_dir}/src ${CMAKE_CXX_FLAGS_RELEASE}")
endif()


