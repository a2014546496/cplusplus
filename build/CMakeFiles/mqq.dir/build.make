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
CMAKE_BINARY_DIR = /home/pt/Desktop/c++/build

# Include any dependencies generated for this target.
include CMakeFiles/mqq.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mqq.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mqq.dir/flags.make

CMakeFiles/mqq.dir/src/SharedMemory.cpp.o: CMakeFiles/mqq.dir/flags.make
CMakeFiles/mqq.dir/src/SharedMemory.cpp.o: /home/pt/Desktop/c++/cplusplus/Concurrency/src/SharedMemory.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pt/Desktop/c++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mqq.dir/src/SharedMemory.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mqq.dir/src/SharedMemory.cpp.o -c /home/pt/Desktop/c++/cplusplus/Concurrency/src/SharedMemory.cpp

CMakeFiles/mqq.dir/src/SharedMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mqq.dir/src/SharedMemory.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pt/Desktop/c++/cplusplus/Concurrency/src/SharedMemory.cpp > CMakeFiles/mqq.dir/src/SharedMemory.cpp.i

CMakeFiles/mqq.dir/src/SharedMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mqq.dir/src/SharedMemory.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pt/Desktop/c++/cplusplus/Concurrency/src/SharedMemory.cpp -o CMakeFiles/mqq.dir/src/SharedMemory.cpp.s

# Object files for target mqq
mqq_OBJECTS = \
"CMakeFiles/mqq.dir/src/SharedMemory.cpp.o"

# External object files for target mqq
mqq_EXTERNAL_OBJECTS =

mqq: CMakeFiles/mqq.dir/src/SharedMemory.cpp.o
mqq: CMakeFiles/mqq.dir/build.make
mqq: CMakeFiles/mqq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pt/Desktop/c++/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mqq"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mqq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mqq.dir/build: mqq

.PHONY : CMakeFiles/mqq.dir/build

CMakeFiles/mqq.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mqq.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mqq.dir/clean

CMakeFiles/mqq.dir/depend:
	cd /home/pt/Desktop/c++/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pt/Desktop/c++/cplusplus/Concurrency /home/pt/Desktop/c++/cplusplus/Concurrency /home/pt/Desktop/c++/build /home/pt/Desktop/c++/build /home/pt/Desktop/c++/build/CMakeFiles/mqq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mqq.dir/depend

