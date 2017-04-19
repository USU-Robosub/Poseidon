if(NOT WIN32 AND NOT DISABLE_COLOR)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
  set(MessageColors Red Green Yellow Blue Magenta Cyan White)
  set(MessageColors ${MessageColors} BoldRed BoldGreen BoldYellow BoldBlue BoldMagenta BoldCyan BoldWhite)
endif()

function(HEADER_DIRECTORIES return_list)
  FILE(GLOB_RECURSE new_list *.h)
  SET(dir_list "")
  FOREACH(file_path ${new_list})
    GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
    SET(dir_list ${dir_list} ${dir_path})
  ENDFOREACH()
  LIST(REMOVE_DUPLICATES dir_list)
  SET(${return_list} ${dir_list} PARENT_SCOPE)
endfunction()

set(MessageTypes STATUS AUTHOR_WARNING WARNING SEND_ERROR FATAL_ERROR)

function(message)
  list(LENGTH ARGV msgLength)
  if(msgLength GREATER 2)
    list(GET ARGV 0 type)
    list(GET ARGV 1 color)
    list(REMOVE_AT ARGV 0)
    LIST(FIND MessageTypes ${type} _index)
    if(${_index} GREATER -1)
      _message(${type} "${${color}}" ${ARGV} "${ColourReset}")
    else()
      list(REMOVE_AT ARGV 0)
      _message("${${type}}" ${ARGV} "${ColourReset}")
    endif()
  elseif(msgLength GREATER 1)
    list(GET ARGV 0 typeOrColor)
    list(REMOVE_AT ARGV 0)
    LIST(FIND MessageTypes ${typeOrColor} _index)
    if(${_index} GREATER -1)
      _message(${typeOrColor} ${ARGV})
    else()
      _message("${${typeOrColor}}" ${ARGV} "${ColourReset}")
    endif()
  else()
    _message(${ARGV})
  endif()
  
endfunction()

function(JOIN VALUES GLUE OUTPUT)
  string (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

function(check_package name)
  list(LENGTH ARGV argLength)
  if(argLength GREATER 1)
    list(GET ARGV 1 required)
  endif()
  string(TOUPPER ${name} upperName)
  message(" ")
  message(BoldYellow "Checking ${name} library status...")
  find_package(${name} ${required})
  if(DEFINED ${upperName}_VERSION)
    message(BoldGreen "${upperName}_VERSION: ${${upperName}_VERSION}")
  endif()
  if(DEFINED ${name}_VERSION)
    message(BoldGreen "${name}_VERSION: ${${name}_VERSION}")
  endif()
  if(DEFINED ${name}_LIBS)
    JOIN("${${name}_LIBS}" " " libs)
    message(BoldGreen "${name}_LIBS: ${libs}")
    set(${name}_LIBS ${${name}_LIBS} PARENT_SCOPE)
  endif()
  if(DEFINED ${name}_INCLUDE_DIRS)
    JOIN("${${name}_INCLUDE_DIRS}" " " includes)
    message(BoldGreen "${name}_INCLUDE_DIRS: ${includes}")
    set(${name}_INCLUDE_DIRS ${${name}_INCLUDE_DIRS} PARENT_SCOPE)
  endif()
  if(DEFINED ${upperName}_INCLUDE_DIR)
    message(BoldGreen "${upperName}_INCLUDE_DIR: ${${upperName}_INCLUDE_DIR}")
    set(${name}_INCLUDE_DIR ${${name}_INCLUDE_DIR} PARENT_SCOPE)
  endif()
  if(${${name}_FOUND})
    set(libStatus "Ready")
    set(libColor BoldCyan)
    set(${name}_FOUND ${${name}_FOUND} PARENT_SCOPE)
  elseif(${${upperName}_FOUND})
    set(libStatus "Ready")
    set(libColor BoldCyan)
    set(${name}_FOUND ${${name}_FOUND} PARENT_SCOPE)
  else()
    set(libStatus "Failed")
    set(libColor BoldRed)
  endif()
  message(${libColor} "${name} library status: [${libStatus}]")
endfunction()

function(check_library name)
  set(NO_VALUE_ERROR "[No value given]")
  message(" ")
  message(BoldYellow "Checking ${name} library status...")
  foreach(path ${ARGV})
    if(${path} STREQUAL REQUIRED)
      set(_isRequired TRUE)
    endif()
    if(NOT ${path} STREQUAL ${name} AND NOT ${path} STREQUAL REQUIRED)
      if(${path})
        get_filename_component(path_loc ${${path}} ABSOLUTE)
      else()
        set(path_loc ${NO_VALUE_ERROR})
      endif()
      if(EXISTS ${path_loc})
        message(BoldGreen "[Found] ${path}: ${path_loc}")
        set(${name}_FOUND TRUE PARENT_SCOPE)
      else()
        message(BoldMagenta "[Not Found] ${path}: ${path_loc}")
        set(${name}_FOUND FALSE PARENT_SCOPE)
        set(LIBRARY_NOTFOUND TRUE)
      endif()
      if(NOT ${path_loc} EQUAL NO_VALUE_ERROR AND NOT IS_ABSOLUTE ${${path}})
        #Set the original path the absolute version
        set(${path} ${path_loc} PARENT_SCOPE)
      endif()
    endif()
  endforeach()
  if(LIBRARY_NOTFOUND)
    message(BoldRed "${name} library status: [Failed]")
    if(_isRequired)
      message(FATAL_ERROR BoldRed "Some parts of the library \"${name}\" could not be found. Because it is required, cmake project configuration cannot continue.")
      #_message(FATAL_ERROR)
    endif()
  else()
    message(BoldCyan "${name} library status: [Ready]")
  endif()
endfunction()