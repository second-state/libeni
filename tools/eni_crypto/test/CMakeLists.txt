add_test(NAME crypto_tests
  COMMAND crypto_tests
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_property(TEST crypto_tests PROPERTY LABELS unittest)
add_test(NAME crypto_so_tests
  COMMAND crypto_so_tests
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/.."
)
set_property(TEST crypto_so_tests PROPERTY LABELS sharedlib regression)

add_executable(crypto_tests
  main.cpp
  HexTest.cpp
  RsaTest.cpp
  ../eni_crypto.cpp
)
target_link_libraries(crypto_tests
  eni
  crypto
  ssl
  skypat
)

add_executable(crypto_so_tests
  main.cpp
  EniTest.cpp
)
target_link_libraries(crypto_so_tests
  eni
  dl
  skypat
)
