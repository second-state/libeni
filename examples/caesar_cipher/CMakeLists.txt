add_test(NAME examples_caesar_cipher COMMAND caesar_cipher_test "Hello World!" "ENI")

add_executable(caesar_cipher_test main.c)
target_link_libraries(caesar_cipher_test
  eni
  dl
)

add_library(eni_caesar_cipher MODULE
  eni_caesar_cipher.cpp
)
set_property(TARGET eni_caesar_cipher
  PROPERTY PREFIX "")
