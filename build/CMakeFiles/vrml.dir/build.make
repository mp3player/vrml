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
CMAKE_SOURCE_DIR = /home/coder/project/c++/vrml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/coder/project/c++/vrml/build

# Include any dependencies generated for this target.
include CMakeFiles/vrml.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/vrml.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/vrml.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vrml.dir/flags.make

CMakeFiles/vrml.dir/main.cc.o: CMakeFiles/vrml.dir/flags.make
CMakeFiles/vrml.dir/main.cc.o: ../main.cc
CMakeFiles/vrml.dir/main.cc.o: CMakeFiles/vrml.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coder/project/c++/vrml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vrml.dir/main.cc.o"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vrml.dir/main.cc.o -MF CMakeFiles/vrml.dir/main.cc.o.d -o CMakeFiles/vrml.dir/main.cc.o -c /home/coder/project/c++/vrml/main.cc

CMakeFiles/vrml.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vrml.dir/main.cc.i"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coder/project/c++/vrml/main.cc > CMakeFiles/vrml.dir/main.cc.i

CMakeFiles/vrml.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vrml.dir/main.cc.s"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coder/project/c++/vrml/main.cc -o CMakeFiles/vrml.dir/main.cc.s

CMakeFiles/vrml.dir/ele.cpp.o: CMakeFiles/vrml.dir/flags.make
CMakeFiles/vrml.dir/ele.cpp.o: ../ele.cpp
CMakeFiles/vrml.dir/ele.cpp.o: CMakeFiles/vrml.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coder/project/c++/vrml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vrml.dir/ele.cpp.o"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vrml.dir/ele.cpp.o -MF CMakeFiles/vrml.dir/ele.cpp.o.d -o CMakeFiles/vrml.dir/ele.cpp.o -c /home/coder/project/c++/vrml/ele.cpp

CMakeFiles/vrml.dir/ele.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vrml.dir/ele.cpp.i"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coder/project/c++/vrml/ele.cpp > CMakeFiles/vrml.dir/ele.cpp.i

CMakeFiles/vrml.dir/ele.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vrml.dir/ele.cpp.s"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coder/project/c++/vrml/ele.cpp -o CMakeFiles/vrml.dir/ele.cpp.s

CMakeFiles/vrml.dir/wrl.cpp.o: CMakeFiles/vrml.dir/flags.make
CMakeFiles/vrml.dir/wrl.cpp.o: ../wrl.cpp
CMakeFiles/vrml.dir/wrl.cpp.o: CMakeFiles/vrml.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/coder/project/c++/vrml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vrml.dir/wrl.cpp.o"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vrml.dir/wrl.cpp.o -MF CMakeFiles/vrml.dir/wrl.cpp.o.d -o CMakeFiles/vrml.dir/wrl.cpp.o -c /home/coder/project/c++/vrml/wrl.cpp

CMakeFiles/vrml.dir/wrl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vrml.dir/wrl.cpp.i"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/coder/project/c++/vrml/wrl.cpp > CMakeFiles/vrml.dir/wrl.cpp.i

CMakeFiles/vrml.dir/wrl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vrml.dir/wrl.cpp.s"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/coder/project/c++/vrml/wrl.cpp -o CMakeFiles/vrml.dir/wrl.cpp.s

# Object files for target vrml
vrml_OBJECTS = \
"CMakeFiles/vrml.dir/main.cc.o" \
"CMakeFiles/vrml.dir/ele.cpp.o" \
"CMakeFiles/vrml.dir/wrl.cpp.o"

# External object files for target vrml
vrml_EXTERNAL_OBJECTS =

vrml: CMakeFiles/vrml.dir/main.cc.o
vrml: CMakeFiles/vrml.dir/ele.cpp.o
vrml: CMakeFiles/vrml.dir/wrl.cpp.o
vrml: CMakeFiles/vrml.dir/build.make
vrml: CMakeFiles/vrml.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/coder/project/c++/vrml/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable vrml"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vrml.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vrml.dir/build: vrml
.PHONY : CMakeFiles/vrml.dir/build

CMakeFiles/vrml.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vrml.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vrml.dir/clean

CMakeFiles/vrml.dir/depend:
	cd /home/coder/project/c++/vrml/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/coder/project/c++/vrml /home/coder/project/c++/vrml /home/coder/project/c++/vrml/build /home/coder/project/c++/vrml/build /home/coder/project/c++/vrml/build/CMakeFiles/vrml.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vrml.dir/depend

