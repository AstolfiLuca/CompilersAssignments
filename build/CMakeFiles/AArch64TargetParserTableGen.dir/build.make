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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/simo/Documents/Compilatori/assignments/CompilersAssignments

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/simo/Documents/Compilatori/assignments/CompilersAssignments/build

# Utility rule file for AArch64TargetParserTableGen.

# Include any custom commands dependencies for this target.
include CMakeFiles/AArch64TargetParserTableGen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AArch64TargetParserTableGen.dir/progress.make

AArch64TargetParserTableGen: CMakeFiles/AArch64TargetParserTableGen.dir/build.make
.PHONY : AArch64TargetParserTableGen

# Rule to build all files generated by this target.
CMakeFiles/AArch64TargetParserTableGen.dir/build: AArch64TargetParserTableGen
.PHONY : CMakeFiles/AArch64TargetParserTableGen.dir/build

CMakeFiles/AArch64TargetParserTableGen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AArch64TargetParserTableGen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AArch64TargetParserTableGen.dir/clean

CMakeFiles/AArch64TargetParserTableGen.dir/depend:
	cd /home/simo/Documents/Compilatori/assignments/CompilersAssignments/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/simo/Documents/Compilatori/assignments/CompilersAssignments /home/simo/Documents/Compilatori/assignments/CompilersAssignments /home/simo/Documents/Compilatori/assignments/CompilersAssignments/build /home/simo/Documents/Compilatori/assignments/CompilersAssignments/build /home/simo/Documents/Compilatori/assignments/CompilersAssignments/build/CMakeFiles/AArch64TargetParserTableGen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/AArch64TargetParserTableGen.dir/depend

