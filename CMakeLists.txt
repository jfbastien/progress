cmake_minimum_required(VERSION 2.8)
project(progress CXX)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()
string(TOUPPER "${CMAKE_BUILD_TYPE}" uppercase_CMAKE_BUILD_TYPE)
if(CMAKE_BUILD_TYPE AND
    NOT uppercase_CMAKE_BUILD_TYPE MATCHES "^(DEBUG|RELEASE|OHMY)$")
  message(FATAL_ERROR "Invalid value for CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

function(add_compile_flag value)
  message(status " Building with ${value}")
  foreach(variable CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
    set(${variable} "${${variable}} ${value}" PARENT_SCOPE)
  endforeach(variable)
endfunction()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND
    CMAKE_GENERATOR STREQUAL "Ninja")
  add_compile_flag("-fcolor-diagnostics")
endif()

add_compile_flag("-std=c++14")
add_compile_flag("-stdlib=libc++")

if(uppercase_CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  add_compile_flag("-O0")
elseif(uppercase_CMAKE_BUILD_TYPE STREQUAL "OHMY")
  add_compile_flag("-OhMy")
else()
  add_compile_flag("-O2")
endif()
add_compile_flag("-g3")
add_compile_flag("-fno-exceptions")
add_compile_flag("-pthread")
add_compile_flag("-Wall")
add_compile_flag("-Wextra")

ADD_LIBRARY(support STATIC print.cc support.cc)


add_executable(synchronous synchronous.cc)
TARGET_LINK_LIBRARIES(synchronous support)

add_executable(volatile_progress volatile_progress.cc)
TARGET_LINK_LIBRARIES(volatile_progress support)
