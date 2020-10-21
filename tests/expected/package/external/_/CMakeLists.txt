find_package(_ ${__MINIMUM_REQUIRED} QUIET COMPONENTS ${__COMPONENTS_REQUIRED})

if(__FOUND)
  message(STATUS "Found _ version ${__MAJOR_VERSION}.${__MINOR_VERSION}.${__SUBMINOR_VERSION}")
  add_library(__external INTERFACE)
else()
  message(STATUS "_ ${__MINIMUM_REQUIRED} could not be located, Building _ instead.")
  include(FetchContent)

  FetchContent_Declare(
    __
    GIT_REPOSITORY https://github.com/darabonba/project.git
    GIT_TAG master)
  
  FetchContent_GetProperties(__)
  if(NOT ___POPULATED)
    FetchContent_Populate(__)
    message(STATUS "Added _ source : ${___SOURCE_DIR}")
    message(STATUS "Added _ binary : ${___BINARY_DIR}")
    add_subdirectory(
      ${___SOURCE_DIR} 
      ${___BINARY_DIR}
    )
    target_include_directories(darabonba_package PRIVATE "${___SOURCE_DIR}/include")
  endif()
endif()
