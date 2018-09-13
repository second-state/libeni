add_test(NAME consensus_tests
  COMMAND consensus.py
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(consensus_tests PROPERTIES
  ENVIRONMENT "T_BINDIR=${CMAKE_BINARY_DIR}"
  LABELS      "regression"
)
