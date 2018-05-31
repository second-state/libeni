add_test(NAME crypto_unittests
  COMMAND crypto_unittests
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(crypto_unittests PROPERTIES LABELS "unittest")

add_executable(crypto_unittests
  main.cpp
  HexTest.cpp
  RsaTest.cpp
  ../eni_crypto.cpp
)
target_link_libraries(crypto_unittests
  eni
  crypto
  ssl
  skypat
)
