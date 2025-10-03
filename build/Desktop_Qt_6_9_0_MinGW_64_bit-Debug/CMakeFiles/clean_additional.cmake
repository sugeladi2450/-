# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\sep2024-template_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\sep2024-template_autogen.dir\\ParseCache.txt"
  "sep2024-template_autogen"
  )
endif()
