file(GLOB tests t[0-9][0-9][0-9][0-9]-*.sh)
foreach(test ${tests})
  string(REGEX REPLACE "(^/.*/)|(\\.sh$)" "" test_name ${test})
  add_test(NAME ${test_name}
    COMMAND ${test}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_tests_properties(${test_name} PROPERTIES
    ENVIRONMENT "T_BINDIR=${CMAKE_BINARY_DIR}"
    LABELS      "auto;regression"
  )
endforeach(test)

add_test(NAME json_tests
  COMMAND json_tests
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/json"
)
set_property(TEST json_tests PROPERTY LABELS json unittest)

add_test(NAME example_tests
  COMMAND so_tests
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)
set_property(TEST example_tests PROPERTY LABELS sharedlib regression)

add_executable(json_tests
  json/main.cpp
  json/ParserTest.cpp
  json/ValueTest.cpp
)
target_link_libraries(json_tests
  eni
  skypat
)

add_executable(so_tests
  examples/main.cpp
  examples/EniTest.cpp
)
target_link_libraries(so_tests
  eni
  dl
  skypat
)
