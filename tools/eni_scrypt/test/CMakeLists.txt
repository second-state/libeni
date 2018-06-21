add_test(NAME scrypt_unittests
  COMMAND scrypt_unittests
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_tests_properties(scrypt_unittests PROPERTIES LABELS "unittest")

add_executable(scrypt_unittests
  main.cpp
  ScryptTest.cpp
  ../eni_scrypt.cpp
  ../scrypt.cpp
)
target_link_libraries(scrypt_unittests
  eni
  crypto
  skypat
)
