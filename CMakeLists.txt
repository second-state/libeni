cmake_minimum_required(VERSION 3.1.0)
project(libeni)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")

include(CTest)

include_directories(PRIVATE
  ${CMAKE_SOURCE_DIR}/include/lity
)

add_library(eni SHARED
  lib/eni.cpp
  lib/json/Object.cpp
  lib/json/Notation.cpp
  lib/json/Value.cpp
  lib/json/Array.cpp
)

find_path(HAVE_SYS_TYPES_H "sys/types.h")
find_path(HAVE_INTTYPES_H "inttypes.h")
find_path(HAVE_STDINT_H "stdint.h")
if(HAVE_SYS_TYPES_H)
	add_definitions(-DHAVE_SYS_TYPES_H)
endif()
if(HAVE_INTTYPES_H)
	add_definitions(-DHAVE_INTTYPES_H)
endif()
if(HAVE_STDINT_H)
	add_definitions(-DHAVE_STDINT_H)
endif()

include(CheckTypeSize)
CHECK_TYPE_SIZE("uint64_t" HAVE_UINT64_T)
CHECK_TYPE_SIZE("u_int64_t" HAVE_U_INT64_T)
if(HAVE_UINT64_T)
	add_definitions(-DHAVE_UINT64_T)
endif()
if(HAVE_U_INT64_T)
	add_definitions(-DHAVE_U_INT64_T)
endif()

add_subdirectory(examples)
add_subdirectory(tools)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
