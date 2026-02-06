find_package(darabonba/test QUIET)

if(darabonba/test_FOUND)
  message(STATUS "Found darabonba/test version ${darabonba/test_VERSION}")
else()
  message(STATUS "darabonba/test could not be located, Building darabonba/test instead.")
  include(FetchContent)

  FetchContent_Declare(
    _darabonba/test
    GIT_REPOSITORY https://github.com/alibabacloud-sdk-cpp/darabonba/test.git
    GIT_TAG master
    CMAKE_ARGS
      -DENABLE_UNIT_TESTS:BOOL="0")

  FetchContent_MakeAvailable(_darabonba/test)
  message(STATUS "Added darabonba/test source : ${_darabonba/test_SOURCE_DIR}")
  message(STATUS "Added darabonba/test binary : ${_darabonba/test_BINARY_DIR}")
endif()