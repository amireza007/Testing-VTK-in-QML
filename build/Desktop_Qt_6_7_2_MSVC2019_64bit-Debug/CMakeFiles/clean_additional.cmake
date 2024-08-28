# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\apphii_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\apphii_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\vtk_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\vtk_autogen.dir\\ParseCache.txt"
  "VTK_autogen"
  "apphii_autogen"
  )
endif()
