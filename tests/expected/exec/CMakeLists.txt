
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(darabonba_exec VERSION "0.1.0")

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< General set up >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> #
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")

if (CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "The C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "The C++ compiler version is: ${CMAKE_CXX_COMPILER_VERSION}")
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Target set up >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> #
add_executable(${PROJECT_NAME} src/exec.cpp)

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< External set up >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> #
add_subdirectory(external)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_library(CPPREST_LIB cpprest)
target_link_libraries(${PROJECT_NAME} PRIVATE crypto  ${Boost_LIBRARIES} ${CPPREST_LIB})
