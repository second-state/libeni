cmake_minimum_required(VERSION 3.1.0)
project(libeni)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")

include(CTest)

include_directories(PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

add_library(eni SHARED
  lib/eni.cpp
  lib/json/Object.cpp
  lib/json/Notation.cpp
  lib/json/Value.cpp
  lib/json/Array.cpp
)

add_subdirectory(examples)
add_subdirectory(tools)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
