# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = "/home/spie-lab-01/ADIP/HW#4/HW_4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/spie-lab-01/ADIP/HW#4/HW_4/build"

# Include any dependencies generated for this target.
include CMakeFiles/HW4_libs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW4_libs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW4_libs.dir/flags.make

CMakeFiles/HW4_libs.dir/src/img_process.cpp.o: CMakeFiles/HW4_libs.dir/flags.make
CMakeFiles/HW4_libs.dir/src/img_process.cpp.o: ../src/img_process.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/spie-lab-01/ADIP/HW#4/HW_4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW4_libs.dir/src/img_process.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW4_libs.dir/src/img_process.cpp.o -c "/home/spie-lab-01/ADIP/HW#4/HW_4/src/img_process.cpp"

CMakeFiles/HW4_libs.dir/src/img_process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_libs.dir/src/img_process.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/spie-lab-01/ADIP/HW#4/HW_4/src/img_process.cpp" > CMakeFiles/HW4_libs.dir/src/img_process.cpp.i

CMakeFiles/HW4_libs.dir/src/img_process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_libs.dir/src/img_process.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/spie-lab-01/ADIP/HW#4/HW_4/src/img_process.cpp" -o CMakeFiles/HW4_libs.dir/src/img_process.cpp.s

CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.requires:

.PHONY : CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.requires

CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.provides: CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.requires
	$(MAKE) -f CMakeFiles/HW4_libs.dir/build.make CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.provides.build
.PHONY : CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.provides

CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.provides.build: CMakeFiles/HW4_libs.dir/src/img_process.cpp.o


# Object files for target HW4_libs
HW4_libs_OBJECTS = \
"CMakeFiles/HW4_libs.dir/src/img_process.cpp.o"

# External object files for target HW4_libs
HW4_libs_EXTERNAL_OBJECTS =

libHW4_libs.a: CMakeFiles/HW4_libs.dir/src/img_process.cpp.o
libHW4_libs.a: CMakeFiles/HW4_libs.dir/build.make
libHW4_libs.a: CMakeFiles/HW4_libs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/spie-lab-01/ADIP/HW#4/HW_4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libHW4_libs.a"
	$(CMAKE_COMMAND) -P CMakeFiles/HW4_libs.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HW4_libs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW4_libs.dir/build: libHW4_libs.a

.PHONY : CMakeFiles/HW4_libs.dir/build

CMakeFiles/HW4_libs.dir/requires: CMakeFiles/HW4_libs.dir/src/img_process.cpp.o.requires

.PHONY : CMakeFiles/HW4_libs.dir/requires

CMakeFiles/HW4_libs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HW4_libs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HW4_libs.dir/clean

CMakeFiles/HW4_libs.dir/depend:
	cd "/home/spie-lab-01/ADIP/HW#4/HW_4/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/spie-lab-01/ADIP/HW#4/HW_4" "/home/spie-lab-01/ADIP/HW#4/HW_4" "/home/spie-lab-01/ADIP/HW#4/HW_4/build" "/home/spie-lab-01/ADIP/HW#4/HW_4/build" "/home/spie-lab-01/ADIP/HW#4/HW_4/build/CMakeFiles/HW4_libs.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/HW4_libs.dir/depend

