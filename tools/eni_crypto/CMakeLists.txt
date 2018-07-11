add_eni_library(eni_crypto
  SRCS eni_crypto.cpp
  LIBS eni
       ssl
       crypto
)

if(BUILD_TESTING)
  include_directories(PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  add_subdirectory(test)
endif()
