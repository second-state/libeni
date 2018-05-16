add_library(eni_reverse MODULE
  reverse/eni_reverse.cpp
)
set_property(TARGET eni_reverse PROPERTY PREFIX "")

add_library(eni_caesar_cipher MODULE
  caesar_cipher/eni_caesar_cipher.cpp
)
set_property(TARGET eni_caesar_cipher PROPERTY PREFIX "")
