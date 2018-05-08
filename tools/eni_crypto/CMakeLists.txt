include_directories(PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(crypto_test demo.c)
target_link_libraries(crypto_test
  eni
  crypto
  ssl
  dl
)

add_library(eni_crypto SHARED
  eni_crypto.cpp
)

add_subdirectory(tests)
