# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/CS-225-Team-NMB-Final-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/CS-225-Team-NMB-Final-Project/build

# Utility rule file for ContinuousStart.

# Include the progress variables for this target.
include _deps/catch2-build/CMakeFiles/ContinuousStart.dir/progress.make

_deps/catch2-build/CMakeFiles/ContinuousStart:
	cd /workspaces/CS-225-Team-NMB-Final-Project/build/_deps/catch2-build && /usr/bin/ctest -D ContinuousStart

ContinuousStart: _deps/catch2-build/CMakeFiles/ContinuousStart
ContinuousStart: _deps/catch2-build/CMakeFiles/ContinuousStart.dir/build.make

.PHONY : ContinuousStart

# Rule to build all files generated by this target.
_deps/catch2-build/CMakeFiles/ContinuousStart.dir/build: ContinuousStart

.PHONY : _deps/catch2-build/CMakeFiles/ContinuousStart.dir/build

_deps/catch2-build/CMakeFiles/ContinuousStart.dir/clean:
	cd /workspaces/CS-225-Team-NMB-Final-Project/build/_deps/catch2-build && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousStart.dir/cmake_clean.cmake
.PHONY : _deps/catch2-build/CMakeFiles/ContinuousStart.dir/clean

_deps/catch2-build/CMakeFiles/ContinuousStart.dir/depend:
	cd /workspaces/CS-225-Team-NMB-Final-Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/CS-225-Team-NMB-Final-Project /workspaces/CS-225-Team-NMB-Final-Project/build/_deps/catch2-src /workspaces/CS-225-Team-NMB-Final-Project/build /workspaces/CS-225-Team-NMB-Final-Project/build/_deps/catch2-build /workspaces/CS-225-Team-NMB-Final-Project/build/_deps/catch2-build/CMakeFiles/ContinuousStart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/catch2-build/CMakeFiles/ContinuousStart.dir/depend
