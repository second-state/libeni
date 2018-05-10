add_test(NAME examples_crypto COMMAND crypto_test "Hello World!")

include_directories(PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(crypto_test demo.c)
target_link_libraries(crypto_test
  eni
  dl
)

add_library(eni_crypto MODULE
  eni_crypto.cpp
)
target_link_libraries(eni_crypto
  ssl
  crypto
)
set_property(TARGET eni_crypto
  PROPERTY PREFIX "")

add_subdirectory(tests)
