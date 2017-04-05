set(CATCH_INCLUDE_DIR ../Libraries/Catch/include)
get_filename_component(CATCH_INCLUDE_DIR ${CATCH_INCLUDE_DIR} ABSOLUTE)

if((NOT CATCH_INCLUDE_DIR) OR (NOT EXISTS ${CATCH_INCLUDE_DIR}))
  message(WARNING "Library 'Catch' could not be found at: ${CATCH_INCLUDE_DIR}.\n"
          "Please initialize its git submodule by running the following command:\n"
          "  `git submodule update --init -- ../Libraries/Catch`\n"
          "or its Windows equivalent.")
  message(STATUS "SLAM unit tests will not be built.")
else()
  message(STATUS "Library 'Catch' was found at ${CATCH_INCLUDE_DIR}.")
  message(STATUS "SLAM unit tests will be built.")
  include_directories(${CATCH_INCLUDE_DIR})
endif()
