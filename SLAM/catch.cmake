set(CATCH_INCLUDE_DIR ../Libraries/Catch/include)
get_filename_component(CATCH_INCLUDE_DIR ${CATCH_INCLUDE_DIR} ABSOLUTE)

if((NOT CATCH_INCLUDE_DIR) OR (NOT EXISTS ${CATCH_INCLUDE_DIR}))
  if(UNIX)
    message(STATUS "Library 'Catch' was not found at ${CATCH_INCLUDE_DIR}.")
    message(STATUS "Attempting to initialize the appropriate git submodule.")
    execute_process(COMMAND git submodule update --init -- ../Libraries/Catch WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    if((NOT CATCH_INCLUDE_DIR) OR (NOT EXISTS ${CATCH_INCLUDE_DIR}))
      message(WARNING "Even after initializing its git submodule, library 'Catch' was not found at ${CATCH_INCLUDE_DIR}.")
    else()
      set(CATCH_FOUND TRUE)
    endif()
  endif()
else()
  set(CATCH_FOUND TRUE)
endif()

if(CATCH_FOUND)
  message(STATUS "Library 'Catch' was found at ${CATCH_INCLUDE_DIR}.")
  message(STATUS "SLAM unit tests will be built.")
  include_directories(${CATCH_INCLUDE_DIR})
else()
  message(WARNING "Library 'Catch' could not be found at: ${CATCH_INCLUDE_DIR}.\n"
          "Please initialize its git submodule by running the following command:\n"
          "  `git submodule update --init -- ../Libraries/Catch`\n"
          "or its Windows equivalent.")
  message(STATUS "SLAM unit tests will not be built.")
endif()