# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/flo/Code/romprogrammer/cli

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/flo/Code/romprogrammer/cli/build

# Include any dependencies generated for this target.
include CMakeFiles/romprg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/romprg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/romprg.dir/flags.make

CMakeFiles/romprg.dir/main.c.o: CMakeFiles/romprg.dir/flags.make
CMakeFiles/romprg.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flo/Code/romprogrammer/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/romprg.dir/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/romprg.dir/main.c.o   -c /home/flo/Code/romprogrammer/cli/main.c

CMakeFiles/romprg.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/romprg.dir/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/flo/Code/romprogrammer/cli/main.c > CMakeFiles/romprg.dir/main.c.i

CMakeFiles/romprg.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/romprg.dir/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/flo/Code/romprogrammer/cli/main.c -o CMakeFiles/romprg.dir/main.c.s

CMakeFiles/romprg.dir/main.c.o.requires:

.PHONY : CMakeFiles/romprg.dir/main.c.o.requires

CMakeFiles/romprg.dir/main.c.o.provides: CMakeFiles/romprg.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/romprg.dir/build.make CMakeFiles/romprg.dir/main.c.o.provides.build
.PHONY : CMakeFiles/romprg.dir/main.c.o.provides

CMakeFiles/romprg.dir/main.c.o.provides.build: CMakeFiles/romprg.dir/main.c.o


CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o: CMakeFiles/romprg.dir/flags.make
CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o: /home/flo/Code/romprogrammer/common/protocol.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flo/Code/romprogrammer/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o   -c /home/flo/Code/romprogrammer/common/protocol.c

CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/flo/Code/romprogrammer/common/protocol.c > CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.i

CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/flo/Code/romprogrammer/common/protocol.c -o CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.s

CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.requires:

.PHONY : CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.requires

CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.provides: CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.requires
	$(MAKE) -f CMakeFiles/romprg.dir/build.make CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.provides.build
.PHONY : CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.provides

CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.provides.build: CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o


CMakeFiles/romprg.dir/serial.c.o: CMakeFiles/romprg.dir/flags.make
CMakeFiles/romprg.dir/serial.c.o: ../serial.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/flo/Code/romprogrammer/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/romprg.dir/serial.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/romprg.dir/serial.c.o   -c /home/flo/Code/romprogrammer/cli/serial.c

CMakeFiles/romprg.dir/serial.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/romprg.dir/serial.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/flo/Code/romprogrammer/cli/serial.c > CMakeFiles/romprg.dir/serial.c.i

CMakeFiles/romprg.dir/serial.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/romprg.dir/serial.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/flo/Code/romprogrammer/cli/serial.c -o CMakeFiles/romprg.dir/serial.c.s

CMakeFiles/romprg.dir/serial.c.o.requires:

.PHONY : CMakeFiles/romprg.dir/serial.c.o.requires

CMakeFiles/romprg.dir/serial.c.o.provides: CMakeFiles/romprg.dir/serial.c.o.requires
	$(MAKE) -f CMakeFiles/romprg.dir/build.make CMakeFiles/romprg.dir/serial.c.o.provides.build
.PHONY : CMakeFiles/romprg.dir/serial.c.o.provides

CMakeFiles/romprg.dir/serial.c.o.provides.build: CMakeFiles/romprg.dir/serial.c.o


# Object files for target romprg
romprg_OBJECTS = \
"CMakeFiles/romprg.dir/main.c.o" \
"CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o" \
"CMakeFiles/romprg.dir/serial.c.o"

# External object files for target romprg
romprg_EXTERNAL_OBJECTS =

romprg: CMakeFiles/romprg.dir/main.c.o
romprg: CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o
romprg: CMakeFiles/romprg.dir/serial.c.o
romprg: CMakeFiles/romprg.dir/build.make
romprg: CMakeFiles/romprg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/flo/Code/romprogrammer/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable romprg"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/romprg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/romprg.dir/build: romprg

.PHONY : CMakeFiles/romprg.dir/build

CMakeFiles/romprg.dir/requires: CMakeFiles/romprg.dir/main.c.o.requires
CMakeFiles/romprg.dir/requires: CMakeFiles/romprg.dir/home/flo/Code/romprogrammer/common/protocol.c.o.requires
CMakeFiles/romprg.dir/requires: CMakeFiles/romprg.dir/serial.c.o.requires

.PHONY : CMakeFiles/romprg.dir/requires

CMakeFiles/romprg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/romprg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/romprg.dir/clean

CMakeFiles/romprg.dir/depend:
	cd /home/flo/Code/romprogrammer/cli/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/flo/Code/romprogrammer/cli /home/flo/Code/romprogrammer/cli /home/flo/Code/romprogrammer/cli/build /home/flo/Code/romprogrammer/cli/build /home/flo/Code/romprogrammer/cli/build/CMakeFiles/romprg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/romprg.dir/depend

