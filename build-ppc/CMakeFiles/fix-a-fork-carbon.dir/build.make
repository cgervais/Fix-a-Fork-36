# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cgervais/Downloads/Fix-a-Fork-36

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc

# Include any dependencies generated for this target.
include CMakeFiles/fix-a-fork-carbon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fix-a-fork-carbon.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fix-a-fork-carbon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fix-a-fork-carbon.dir/flags.make

CMakeFiles/fix-a-fork-carbon.dir/main.c.obj: CMakeFiles/fix-a-fork-carbon.dir/flags.make
CMakeFiles/fix-a-fork-carbon.dir/main.c.obj: /Users/cgervais/Downloads/Fix-a-Fork-36/main.c
CMakeFiles/fix-a-fork-carbon.dir/main.c.obj: CMakeFiles/fix-a-fork-carbon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/fix-a-fork-carbon.dir/main.c.obj"
	/Users/cgervais/Documents/Code/Retro68-build/toolchain/bin/powerpc-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/fix-a-fork-carbon.dir/main.c.obj -MF CMakeFiles/fix-a-fork-carbon.dir/main.c.obj.d -o CMakeFiles/fix-a-fork-carbon.dir/main.c.obj -c /Users/cgervais/Downloads/Fix-a-Fork-36/main.c

CMakeFiles/fix-a-fork-carbon.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/fix-a-fork-carbon.dir/main.c.i"
	/Users/cgervais/Documents/Code/Retro68-build/toolchain/bin/powerpc-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/cgervais/Downloads/Fix-a-Fork-36/main.c > CMakeFiles/fix-a-fork-carbon.dir/main.c.i

CMakeFiles/fix-a-fork-carbon.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/fix-a-fork-carbon.dir/main.c.s"
	/Users/cgervais/Documents/Code/Retro68-build/toolchain/bin/powerpc-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/cgervais/Downloads/Fix-a-Fork-36/main.c -o CMakeFiles/fix-a-fork-carbon.dir/main.c.s

CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj: CMakeFiles/fix-a-fork-carbon.dir/flags.make
CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj: /Users/cgervais/Downloads/Fix-a-Fork-36/file_ext.c
CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj: CMakeFiles/fix-a-fork-carbon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj"
	/Users/cgervais/Documents/Code/Retro68-build/toolchain/bin/powerpc-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj -MF CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj.d -o CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj -c /Users/cgervais/Downloads/Fix-a-Fork-36/file_ext.c

CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.i"
	/Users/cgervais/Documents/Code/Retro68-build/toolchain/bin/powerpc-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/cgervais/Downloads/Fix-a-Fork-36/file_ext.c > CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.i

CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.s"
	/Users/cgervais/Documents/Code/Retro68-build/toolchain/bin/powerpc-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/cgervais/Downloads/Fix-a-Fork-36/file_ext.c -o CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.s

# Object files for target fix-a-fork-carbon
fix__a__fork__carbon_OBJECTS = \
"CMakeFiles/fix-a-fork-carbon.dir/main.c.obj" \
"CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj"

# External object files for target fix-a-fork-carbon
fix__a__fork__carbon_EXTERNAL_OBJECTS =

fix-a-fork-carbon.xcoff: CMakeFiles/fix-a-fork-carbon.dir/main.c.obj
fix-a-fork-carbon.xcoff: CMakeFiles/fix-a-fork-carbon.dir/file_ext.c.obj
fix-a-fork-carbon.xcoff: CMakeFiles/fix-a-fork-carbon.dir/build.make
fix-a-fork-carbon.xcoff: CMakeFiles/fix-a-fork-carbon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable fix-a-fork-carbon.xcoff"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fix-a-fork-carbon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fix-a-fork-carbon.dir/build: fix-a-fork-carbon.xcoff
.PHONY : CMakeFiles/fix-a-fork-carbon.dir/build

CMakeFiles/fix-a-fork-carbon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fix-a-fork-carbon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fix-a-fork-carbon.dir/clean

CMakeFiles/fix-a-fork-carbon.dir/depend:
	cd /Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cgervais/Downloads/Fix-a-Fork-36 /Users/cgervais/Downloads/Fix-a-Fork-36 /Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc /Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc /Users/cgervais/Downloads/Fix-a-Fork-36/build-ppc/CMakeFiles/fix-a-fork-carbon.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fix-a-fork-carbon.dir/depend

