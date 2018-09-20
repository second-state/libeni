configure_file(tests.json.in tests.json)
add_test(NAME consensus_tests
  COMMAND consensus.py "${CMAKE_CURRENT_BINARY_DIR}/tests.json"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(consensus_tests PROPERTIES
  ENVIRONMENT "PATH=$ENV{PATH}:${CMAKE_BINARY_DIR}/tools/eni_cli;\
               LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}"
  LABELS      "regression"
)
