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
CMAKE_SOURCE_DIR = /home/pt/Desktop/c++/cplusplus/Concurrency

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pt/Desktop/c++/cplusplus/Concurrency/build

# Include any dependencies generated for this target.
include CMakeFiles/cpp-compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp-compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp-compiler.dir/flags.make

CMakeFiles/cpp-compiler.dir/thread01.cpp.o: CMakeFiles/cpp-compiler.dir/flags.make
CMakeFiles/cpp-compiler.dir/thread01.cpp.o: ../thread01.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pt/Desktop/c++/cplusplus/Concurrency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp-compiler.dir/thread01.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpp-compiler.dir/thread01.cpp.o -c /home/pt/Desktop/c++/cplusplus/Concurrency/thread01.cpp

CMakeFiles/cpp-compiler.dir/thread01.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp-compiler.dir/thread01.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pt/Desktop/c++/cplusplus/Concurrency/thread01.cpp > CMakeFiles/cpp-compiler.dir/thread01.cpp.i

CMakeFiles/cpp-compiler.dir/thread01.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp-compiler.dir/thread01.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pt/Desktop/c++/cplusplus/Concurrency/thread01.cpp -o CMakeFiles/cpp-compiler.dir/thread01.cpp.s

# Object files for target cpp-compiler
cpp__compiler_OBJECTS = \
"CMakeFiles/cpp-compiler.dir/thread01.cpp.o"

# External object files for target cpp-compiler
cpp__compiler_EXTERNAL_OBJECTS =

cpp-compiler: CMakeFiles/cpp-compiler.dir/thread01.cpp.o
cpp-compiler: CMakeFiles/cpp-compiler.dir/build.make
cpp-compiler: CMakeFiles/cpp-compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pt/Desktop/c++/cplusplus/Concurrency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpp-compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpp-compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp-compiler.dir/build: cpp-compiler

.PHONY : CMakeFiles/cpp-compiler.dir/build

CMakeFiles/cpp-compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpp-compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpp-compiler.dir/clean

CMakeFiles/cpp-compiler.dir/depend:
	cd /home/pt/Desktop/c++/cplusplus/Concurrency/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pt/Desktop/c++/cplusplus/Concurrency /home/pt/Desktop/c++/cplusplus/Concurrency /home/pt/Desktop/c++/cplusplus/Concurrency/build /home/pt/Desktop/c++/cplusplus/Concurrency/build /home/pt/Desktop/c++/cplusplus/Concurrency/build/CMakeFiles/cpp-compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpp-compiler.dir/depend

