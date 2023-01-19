cmake_minimum_required(VERSION 3.22)

project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(bench perf/benchmark.cpp)
add_executable(test tests/test.cpp)

include(FetchContent)
FetchContent_Declare(
  onetbb
  GIT_REPOSITORY https://github.com/oneapi-src/oneTBB.git
  GIT_TAG v2021.6.0
)
include(FetchContent)
FetchContent_Declare(parlaylib
  GIT_REPOSITORY  https://github.com/cmuparlay/parlaylib.git
  GIT_TAG         master
)
FetchContent_GetProperties(parlaylib)
if(NOT parlaylib_POPULATED)
  FetchContent_Populate(parlaylib)  
  add_subdirectory(${parlaylib_SOURCE_DIR} EXCLUDE_FROM_ALL)
endif()
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.7.1
)

FetchContent_MakeAvailable(
  onetbb
  googletest
  googlebenchmark
  parlaylib
)

target_link_libraries(bench PRIVATE TBB::tbb benchmark::benchmark parlay GTest::gtest_main)
target_link_libraries(test PRIVATE TBB::tbb benchmark::benchmark parlay GTest::gtest_main)