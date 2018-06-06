add_library(eni_reverse MODULE
  reverse/eni_reverse.cpp
)
target_link_libraries(eni_reverse eni)
set_property(TARGET eni_reverse PROPERTY PREFIX "")

add_library(eni_caesar_cipher MODULE
  caesar_cipher/eni_caesar_cipher.cpp
)
target_link_libraries(eni_caesar_cipher eni)
set_property(TARGET eni_caesar_cipher PROPERTY PREFIX "")
