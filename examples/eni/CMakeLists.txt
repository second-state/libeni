add_test(NAME examples_eni COMMAND eni_test "Hello World")

add_executable(eni_test main.c)
target_link_libraries(eni_test
  eni
  dl
)

add_library(eni_reverse MODULE
  eni_reverse.cpp
)
set_property(TARGET eni_reverse
  PROPERTY PREFIX "")
