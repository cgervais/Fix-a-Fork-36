
cmake_minimum_required(VERSION 3.9)

project(fix-a-fork-carbon)
add_application(fix-a-fork-carbon CREATOR "FAF " main.c file_ext.c Fix-a-Fork-Carbon.rsrc)
IF(CMAKE_SYSTEM_NAME MATCHES Retro68)
  set_target_properties(fix-a-fork-carbon PROPERTIES COMPILE_FLAGS "-ffunction-sections -mcpu=601 -O3 -Wall -Wextra -Wno-unused-parameter")
  set_target_properties(fix-a-fork-carbon PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
  target_link_libraries(CarbonLib)
ENDIF()
