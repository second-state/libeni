add_eni_library(eni_scrypt
  SRCS eni_scrypt.cpp
       scrypt.cpp
  LIBS eni
       crypto
)

if(BUILD_TESTING)
  include_directories(PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  add_subdirectory(test)
endif()
