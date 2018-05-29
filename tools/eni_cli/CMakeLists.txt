add_executable(eni_gas
  optParser.cpp
  eni_gas.cpp
)
target_link_libraries(eni_gas dl eni)

add_executable(eni_run
  optParser.cpp
  eni_run.cpp
)
target_link_libraries(eni_run dl eni)

if(BUILD_TESTING)
  include_directories(PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )

  add_subdirectory(test)
endif()
