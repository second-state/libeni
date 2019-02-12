file(GLOB tests t[0-9][0-9][0-9][0-9]-*.sh)
foreach(test ${tests})
  string(REGEX REPLACE "(^/.*/)|(\\.sh$)" "" test_name ${test})
  string(REGEX MATCH "^t[0-9][0-9][0-9][0-9]" test_id ${test_name})
  add_test(NAME ${test_name}
    COMMAND ${test}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
  set_tests_properties(${test_name} PROPERTIES
    ENVIRONMENT "T_BINDIR=${CMAKE_BINARY_DIR};T_NAME=${test_name};T_ID=${test_id}"
    LABELS      "auto;regression"
  )
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${test_id}/CMakeLists.txt")
    add_subdirectory(${test_id})
  endif()
endforeach(test)

add_subdirectory(consensus)
add_subdirectory(unittests)
