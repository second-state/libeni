add_test(NAME examples_json
  COMMAND json_test "ex3.json"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(json_test main.cpp)
target_link_libraries(json_test
  eni
)
