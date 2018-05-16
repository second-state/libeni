add_library(eni_crypto MODULE
  eni_crypto.cpp
)
target_link_libraries(eni_crypto
  ssl
  crypto
)
set_property(TARGET eni_crypto PROPERTY PREFIX "")

if(BUILD_TESTING)
  include_directories(PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )

  add_subdirectory(test)
endif()
