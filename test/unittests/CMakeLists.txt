add_test(NAME unittests
  COMMAND unittests
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(unittests PROPERTIES LABELS "unittest")

add_executable(unittests
  main.cpp
  EniTypesTest.cpp
  json/ArrayTest.cpp
  json/ParserTest.cpp
  json/ValueTest.cpp
  adt/HashTableTest.cpp
  adt/StringHashTableTest.cpp
  adt/StringMapTest.cpp
  adt/VectorTest.cpp
  adt/PointerIteratorTest.cpp
  diagnostic/ExceptionTest.cpp
)
target_link_libraries(unittests
  eni
  skypat
)
