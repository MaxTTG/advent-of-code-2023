# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/AdventOfCode2023/day14

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/AdventOfCode2023/day14/build

# Include any dependencies generated for this target.
include CMakeFiles/day14.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/day14.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/day14.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day14.dir/flags.make

CMakeFiles/day14.dir/main.cpp.o: CMakeFiles/day14.dir/flags.make
CMakeFiles/day14.dir/main.cpp.o: ../main.cpp
CMakeFiles/day14.dir/main.cpp.o: CMakeFiles/day14.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/AdventOfCode2023/day14/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/day14.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/day14.dir/main.cpp.o -MF CMakeFiles/day14.dir/main.cpp.o.d -o CMakeFiles/day14.dir/main.cpp.o -c /root/AdventOfCode2023/day14/main.cpp

CMakeFiles/day14.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/day14.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/AdventOfCode2023/day14/main.cpp > CMakeFiles/day14.dir/main.cpp.i

CMakeFiles/day14.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/day14.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/AdventOfCode2023/day14/main.cpp -o CMakeFiles/day14.dir/main.cpp.s

# Object files for target day14
day14_OBJECTS = \
"CMakeFiles/day14.dir/main.cpp.o"

# External object files for target day14
day14_EXTERNAL_OBJECTS =

day14: CMakeFiles/day14.dir/main.cpp.o
day14: CMakeFiles/day14.dir/build.make
day14: CMakeFiles/day14.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/AdventOfCode2023/day14/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable day14"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day14.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day14.dir/build: day14
.PHONY : CMakeFiles/day14.dir/build

CMakeFiles/day14.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day14.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day14.dir/clean

CMakeFiles/day14.dir/depend:
	cd /root/AdventOfCode2023/day14/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/AdventOfCode2023/day14 /root/AdventOfCode2023/day14 /root/AdventOfCode2023/day14/build /root/AdventOfCode2023/day14/build /root/AdventOfCode2023/day14/build/CMakeFiles/day14.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day14.dir/depend

