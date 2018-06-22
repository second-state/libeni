add_test(NAME unittests
  COMMAND unittests
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(unittests PROPERTIES LABELS "unittest")

add_executable(unittests
  main.cpp
  json/ParserTest.cpp
  json/ValueTest.cpp
  lity/HashTableTest.cpp
  lity/StringRefTest.cpp
  lity/TypeTraitsTest.cpp
)
target_link_libraries(unittests
  eni
  skypat
)
