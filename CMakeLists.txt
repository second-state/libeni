cmake_minimum_required(VERSION 3.1.0)
project(libeni)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC")

include(CTest)

function(add_eni_library target)
  set(multival_args SRCS LIBS)
  cmake_parse_arguments(ENILIB "" "" "${multival_args}" "${ARGN}")

  #[[Build the library as ${target}.so (without the "lib" prefix).]]
  add_library(${target} MODULE ${ENILIB_SRCS})
  target_link_libraries(${target} ${ENILIB_LIBS})
  set_property(TARGET ${target} PROPERTY PREFIX "")

  #[[Generate sha512 checksum of the library as ${target}.so.sha512.]]
  set(target_file $<TARGET_FILE_NAME:${target}>)
  set(target_checksum ${target_file}.sha512)
  add_custom_target(${target}_checksum ALL
    COMMAND sha512sum -b ${target_file} > ${target_checksum}
    DEPENDS ${TARGET}
  )

  #[[Add a test-case to check the generated checksum.]]
  add_test(NAME ${target}_checksum_test
    COMMAND sha512sum -c ${target_checksum}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
  set_tests_properties(${target}_checksum_test PROPERTIES
    LABELS "auto;checksum"
  )
endfunction() #[[End of add_eni_library().]]

include_directories(PRIVATE
  ${CMAKE_SOURCE_DIR}/include/eni
)

add_library(eni SHARED
  lib/eni.cpp
  lib/json/Object.cpp
  lib/json/Notation.cpp
  lib/json/Value.cpp
  lib/json/Array.cpp
  lib/diagnostic/Exception.cpp
)

add_subdirectory(examples)
add_subdirectory(tools)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
