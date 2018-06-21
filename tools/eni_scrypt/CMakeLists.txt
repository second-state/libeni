add_library(eni_scrypt MODULE
  eni_scrypt.cpp
  scrypt.cpp
)
target_link_libraries(eni_scrypt
  eni
  crypto
)
set_property(TARGET eni_scrypt PROPERTY PREFIX "")

if(BUILD_TESTING)
  include_directories(PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )

  add_subdirectory(test)
endif()
