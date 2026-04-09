find_package(import QUIET)

if(import_FOUND)
  message(STATUS "Found import version ${import_VERSION}")
else()
  message(STATUS "import could not be located, Building import instead.")
  include(FetchContent)

  FetchContent_Declare(
    _import
    GIT_REPOSITORY https://github.com/alibabacloud-sdk-cpp/import.git
    GIT_TAG master
    CMAKE_ARGS
      -DENABLE_UNIT_TESTS:BOOL="0")

  FetchContent_MakeAvailable(_import)
  message(STATUS "Added import source : ${_import_SOURCE_DIR}")
  message(STATUS "Added import binary : ${_import_BINARY_DIR}")
endif()