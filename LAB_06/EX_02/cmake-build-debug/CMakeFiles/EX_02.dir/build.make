# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/EX_02.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/EX_02.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EX_02.dir/flags.make

CMakeFiles/EX_02.dir/main.c.obj: CMakeFiles/EX_02.dir/flags.make
CMakeFiles/EX_02.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/EX_02.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\EX_02.dir\main.c.obj -c C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\main.c

CMakeFiles/EX_02.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/EX_02.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\main.c > CMakeFiles\EX_02.dir\main.c.i

CMakeFiles/EX_02.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/EX_02.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\main.c -o CMakeFiles\EX_02.dir\main.c.s

# Object files for target EX_02
EX_02_OBJECTS = \
"CMakeFiles/EX_02.dir/main.c.obj"

# External object files for target EX_02
EX_02_EXTERNAL_OBJECTS =

EX_02.exe: CMakeFiles/EX_02.dir/main.c.obj
EX_02.exe: CMakeFiles/EX_02.dir/build.make
EX_02.exe: CMakeFiles/EX_02.dir/linklibs.rsp
EX_02.exe: CMakeFiles/EX_02.dir/objects1.rsp
EX_02.exe: CMakeFiles/EX_02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable EX_02.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\EX_02.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EX_02.dir/build: EX_02.exe
.PHONY : CMakeFiles/EX_02.dir/build

CMakeFiles/EX_02.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\EX_02.dir\cmake_clean.cmake
.PHONY : CMakeFiles/EX_02.dir/clean

CMakeFiles/EX_02.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02 C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02 C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\cmake-build-debug C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\cmake-build-debug C:\Users\wizodts\CLionProjects\APA\LAB_06\EX_02\cmake-build-debug\CMakeFiles\EX_02.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EX_02.dir/depend

