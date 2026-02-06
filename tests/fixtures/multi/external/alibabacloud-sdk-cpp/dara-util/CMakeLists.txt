find_package(alibabacloud-sdk-cpp/dara-util QUIET)

if(alibabacloud-sdk-cpp/dara-util_FOUND)
  message(STATUS "Found alibabacloud-sdk-cpp/dara-util version ${alibabacloud-sdk-cpp/dara-util_VERSION}")
else()
  message(STATUS "alibabacloud-sdk-cpp/dara-util could not be located, Building alibabacloud-sdk-cpp/dara-util instead.")
  include(FetchContent)

  FetchContent_Declare(
    _alibabacloud-sdk-cpp/dara-util
    GIT_REPOSITORY https://github.com/alibabacloud-sdk-cpp/alibabacloud-sdk-cpp/dara-util.git
    GIT_TAG master
    CMAKE_ARGS
      -DENABLE_UNIT_TESTS:BOOL="0")

  FetchContent_MakeAvailable(_alibabacloud-sdk-cpp/dara-util)
  message(STATUS "Added alibabacloud-sdk-cpp/dara-util source : ${_alibabacloud-sdk-cpp/dara-util_SOURCE_DIR}")
  message(STATUS "Added alibabacloud-sdk-cpp/dara-util binary : ${_alibabacloud-sdk-cpp/dara-util_BINARY_DIR}")
endif()