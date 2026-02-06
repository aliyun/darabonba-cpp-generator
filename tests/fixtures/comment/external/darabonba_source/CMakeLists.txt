find_package(darabonba_source QUIET)

if(darabonba_source_FOUND)
  message(STATUS "Found darabonba_source version ${darabonba_source_VERSION}")
else()
  message(STATUS "darabonba_source could not be located, Building darabonba_source instead.")
  include(FetchContent)

  FetchContent_Declare(
    _darabonba_source
    GIT_REPOSITORY https://github.com/alibabacloud-sdk-cpp/darabonba-source.git
    GIT_TAG master
    CMAKE_ARGS
      -DENABLE_UNIT_TESTS:BOOL="0")

  FetchContent_MakeAvailable(_darabonba_source)
  message(STATUS "Added darabonba_source source : ${_darabonba_source_SOURCE_DIR}")
  message(STATUS "Added darabonba_source binary : ${_darabonba_source_BINARY_DIR}")
endif()