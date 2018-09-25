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

configure_file(malformed.json.in malformed.json)
add_test(NAME malformed_consensus_tests
  COMMAND consensus.py "${CMAKE_CURRENT_BINARY_DIR}/malformed.json"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(malformed_consensus_tests PROPERTIES
  PASS_REGULAR_EXPRESSION "ERROR: failed to expand arguments"
)
