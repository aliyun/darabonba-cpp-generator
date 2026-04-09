find_package(source QUIET)

if(source_FOUND)
  message(STATUS "Found source version ${source_VERSION}")
else()
  message(STATUS "source could not be located, Building source instead.")
  include(FetchContent)

  FetchContent_Declare(
    _source
    GIT_REPOSITORY https://github.com/alibabacloud-sdk-cpp/source.git
    GIT_TAG master
    CMAKE_ARGS
      -DENABLE_UNIT_TESTS:BOOL="0")

  FetchContent_MakeAvailable(_source)
  message(STATUS "Added source source : ${_source_SOURCE_DIR}")
  message(STATUS "Added source binary : ${_source_BINARY_DIR}")
endif()