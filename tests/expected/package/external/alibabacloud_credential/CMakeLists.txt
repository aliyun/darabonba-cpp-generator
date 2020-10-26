find_package(alibabacloud_credential ${alibabacloud_credential_MINIMUM_REQUIRED} QUIET COMPONENTS ${alibabacloud_credential_COMPONENTS_REQUIRED})

if(alibabacloud_credential_FOUND)
  message(STATUS "Found alibabacloud_credential version ${alibabacloud_credential_MAJOR_VERSION}.${alibabacloud_credential_MINOR_VERSION}.${alibabacloud_credential_SUBMINOR_VERSION}")
  add_library(alibabacloud_credential_external INTERFACE)
else()
  message(STATUS "alibabacloud_credential ${alibabacloud_credential_MINIMUM_REQUIRED} could not be located, Building alibabacloud_credential instead.")
  include(FetchContent)

  FetchContent_Declare(
    _alibabacloud_credential
    GIT_REPOSITORY https://github.com/aliyun/credential-cpp.git
    GIT_TAG master)
  
  FetchContent_GetProperties(_alibabacloud_credential)
  if(NOT _alibabacloud_credential_POPULATED)
    FetchContent_Populate(_alibabacloud_credential)
    message(STATUS "Added alibabacloud_credential source : ${_alibabacloud_credential_SOURCE_DIR}")
    message(STATUS "Added alibabacloud_credential binary : ${_alibabacloud_credential_BINARY_DIR}")
    add_subdirectory(
      ${_alibabacloud_credential_SOURCE_DIR} 
      ${_alibabacloud_credential_BINARY_DIR}
    )
  endif()
  target_include_directories(darabonba_package PRIVATE "${_alibabacloud_credential_SOURCE_DIR}/include")
  if(ENABLE_UNIT_TESTS)
    target_include_directories(tests_darabonba_package PRIVATE "${_alibabacloud_credential_SOURCE_DIR}/include")
  endif()
endif()
