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
CMAKE_SOURCE_DIR = /home/daniil/cpp/Otus_async_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daniil/cpp/Otus_async_lib/build

# Include any dependencies generated for this target.
include CMakeFiles/bulk.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bulk.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bulk.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bulk.dir/flags.make

CMakeFiles/bulk.dir/main.cpp.o: CMakeFiles/bulk.dir/flags.make
CMakeFiles/bulk.dir/main.cpp.o: ../main.cpp
CMakeFiles/bulk.dir/main.cpp.o: CMakeFiles/bulk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daniil/cpp/Otus_async_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bulk.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bulk.dir/main.cpp.o -MF CMakeFiles/bulk.dir/main.cpp.o.d -o CMakeFiles/bulk.dir/main.cpp.o -c /home/daniil/cpp/Otus_async_lib/main.cpp

CMakeFiles/bulk.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bulk.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daniil/cpp/Otus_async_lib/main.cpp > CMakeFiles/bulk.dir/main.cpp.i

CMakeFiles/bulk.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bulk.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daniil/cpp/Otus_async_lib/main.cpp -o CMakeFiles/bulk.dir/main.cpp.s

# Object files for target bulk
bulk_OBJECTS = \
"CMakeFiles/bulk.dir/main.cpp.o"

# External object files for target bulk
bulk_EXTERNAL_OBJECTS =

bulk: CMakeFiles/bulk.dir/main.cpp.o
bulk: CMakeFiles/bulk.dir/build.make
bulk: libasync.a
bulk: lib_State_mch.a
bulk: CMakeFiles/bulk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daniil/cpp/Otus_async_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bulk"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bulk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bulk.dir/build: bulk
.PHONY : CMakeFiles/bulk.dir/build

CMakeFiles/bulk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bulk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bulk.dir/clean

CMakeFiles/bulk.dir/depend:
	cd /home/daniil/cpp/Otus_async_lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daniil/cpp/Otus_async_lib /home/daniil/cpp/Otus_async_lib /home/daniil/cpp/Otus_async_lib/build /home/daniil/cpp/Otus_async_lib/build /home/daniil/cpp/Otus_async_lib/build/CMakeFiles/bulk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bulk.dir/depend

