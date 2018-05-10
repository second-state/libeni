add_test(NAME test_eni_crypto_hex
  COMMAND hex_test "A+!"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_test(NAME test_eni_crypto_rsa
  COMMAND rsa_test "Hello World!"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(hex_test
  hex.cpp
  ../eni_crypto.cpp)
target_link_libraries(hex_test
  eni
  crypto
  ssl
)

add_executable(rsa_test
  rsa.cpp
  ../eni_crypto.cpp)
target_link_libraries(rsa_test
  eni
  crypto
  ssl
)
