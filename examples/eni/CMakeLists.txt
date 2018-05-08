add_test(NAME examples_eni COMMAND eni_test 'Hello World')

add_executable(eni_test main.c)
target_link_libraries(eni_test
  eni
  dl
)

add_library(eni_reverse SHARED
  eni_reverse.cpp
)
