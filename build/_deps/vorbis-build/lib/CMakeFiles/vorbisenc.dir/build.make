# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/greenbox/projects/sfmltest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/greenbox/projects/sfmltest/build

# Include any dependencies generated for this target.
include _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/flags.make

_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/codegen:
.PHONY : _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/codegen

_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.o: _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/flags.make
_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.o: _deps/vorbis-src/lib/vorbisenc.c
_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.o: _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/greenbox/projects/sfmltest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.o"
	cd /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.o -MF CMakeFiles/vorbisenc.dir/vorbisenc.c.o.d -o CMakeFiles/vorbisenc.dir/vorbisenc.c.o -c /Users/greenbox/projects/sfmltest/build/_deps/vorbis-src/lib/vorbisenc.c

_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/vorbisenc.dir/vorbisenc.c.i"
	cd /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/greenbox/projects/sfmltest/build/_deps/vorbis-src/lib/vorbisenc.c > CMakeFiles/vorbisenc.dir/vorbisenc.c.i

_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/vorbisenc.dir/vorbisenc.c.s"
	cd /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/greenbox/projects/sfmltest/build/_deps/vorbis-src/lib/vorbisenc.c -o CMakeFiles/vorbisenc.dir/vorbisenc.c.s

# Object files for target vorbisenc
vorbisenc_OBJECTS = \
"CMakeFiles/vorbisenc.dir/vorbisenc.c.o"

# External object files for target vorbisenc
vorbisenc_EXTERNAL_OBJECTS =

_deps/sfml-build/lib/libvorbisencd.a: _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/vorbisenc.c.o
_deps/sfml-build/lib/libvorbisencd.a: _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/build.make
_deps/sfml-build/lib/libvorbisencd.a: _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/greenbox/projects/sfmltest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library ../../sfml-build/lib/libvorbisencd.a"
	cd /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib && $(CMAKE_COMMAND) -P CMakeFiles/vorbisenc.dir/cmake_clean_target.cmake
	cd /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vorbisenc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/build: _deps/sfml-build/lib/libvorbisencd.a
.PHONY : _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/build

_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/clean:
	cd /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib && $(CMAKE_COMMAND) -P CMakeFiles/vorbisenc.dir/cmake_clean.cmake
.PHONY : _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/clean

_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/depend:
	cd /Users/greenbox/projects/sfmltest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/greenbox/projects/sfmltest /Users/greenbox/projects/sfmltest/build/_deps/vorbis-src/lib /Users/greenbox/projects/sfmltest/build /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib /Users/greenbox/projects/sfmltest/build/_deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/vorbis-build/lib/CMakeFiles/vorbisenc.dir/depend

