# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /home/wombat-laptop/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/wombat-laptop/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wombat-laptop/GitLab/SO-project/SoThredsApp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SoThredsApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SoThredsApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SoThredsApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SoThredsApp.dir/flags.make

CMakeFiles/SoThredsApp.dir/main/main.cpp.o: CMakeFiles/SoThredsApp.dir/flags.make
CMakeFiles/SoThredsApp.dir/main/main.cpp.o: /home/wombat-laptop/GitLab/SO-project/SoThredsApp/main/main.cpp
CMakeFiles/SoThredsApp.dir/main/main.cpp.o: CMakeFiles/SoThredsApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SoThredsApp.dir/main/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SoThredsApp.dir/main/main.cpp.o -MF CMakeFiles/SoThredsApp.dir/main/main.cpp.o.d -o CMakeFiles/SoThredsApp.dir/main/main.cpp.o -c /home/wombat-laptop/GitLab/SO-project/SoThredsApp/main/main.cpp

CMakeFiles/SoThredsApp.dir/main/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SoThredsApp.dir/main/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wombat-laptop/GitLab/SO-project/SoThredsApp/main/main.cpp > CMakeFiles/SoThredsApp.dir/main/main.cpp.i

CMakeFiles/SoThredsApp.dir/main/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SoThredsApp.dir/main/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wombat-laptop/GitLab/SO-project/SoThredsApp/main/main.cpp -o CMakeFiles/SoThredsApp.dir/main/main.cpp.s

CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o: CMakeFiles/SoThredsApp.dir/flags.make
CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o: /home/wombat-laptop/GitLab/SO-project/SoThredsApp/map/MainAppMap.cpp
CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o: CMakeFiles/SoThredsApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o -MF CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o.d -o CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o -c /home/wombat-laptop/GitLab/SO-project/SoThredsApp/map/MainAppMap.cpp

CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wombat-laptop/GitLab/SO-project/SoThredsApp/map/MainAppMap.cpp > CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.i

CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wombat-laptop/GitLab/SO-project/SoThredsApp/map/MainAppMap.cpp -o CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.s

CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o: CMakeFiles/SoThredsApp.dir/flags.make
CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o: /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/mapRender/MapRender.cpp
CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o: CMakeFiles/SoThredsApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o -MF CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o.d -o CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o -c /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/mapRender/MapRender.cpp

CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/mapRender/MapRender.cpp > CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.i

CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/mapRender/MapRender.cpp -o CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.s

CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o: CMakeFiles/SoThredsApp.dir/flags.make
CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o: /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/switch/SwitchThread.cpp
CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o: CMakeFiles/SoThredsApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o -MF CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o.d -o CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o -c /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/switch/SwitchThread.cpp

CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/switch/SwitchThread.cpp > CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.i

CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/switch/SwitchThread.cpp -o CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.s

CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o: CMakeFiles/SoThredsApp.dir/flags.make
CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o: /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entity/Person.cpp
CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o: CMakeFiles/SoThredsApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o -MF CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o.d -o CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o -c /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entity/Person.cpp

CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entity/Person.cpp > CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.i

CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entity/Person.cpp -o CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.s

CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o: CMakeFiles/SoThredsApp.dir/flags.make
CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o: /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entityGenerator/EntityGenerator.cpp
CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o: CMakeFiles/SoThredsApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o -MF CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o.d -o CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o -c /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entityGenerator/EntityGenerator.cpp

CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entityGenerator/EntityGenerator.cpp > CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.i

CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wombat-laptop/GitLab/SO-project/SoThredsApp/threads/entityGenerator/EntityGenerator.cpp -o CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.s

# Object files for target SoThredsApp
SoThredsApp_OBJECTS = \
"CMakeFiles/SoThredsApp.dir/main/main.cpp.o" \
"CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o" \
"CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o" \
"CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o" \
"CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o" \
"CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o"

# External object files for target SoThredsApp
SoThredsApp_EXTERNAL_OBJECTS =

SoThredsApp: CMakeFiles/SoThredsApp.dir/main/main.cpp.o
SoThredsApp: CMakeFiles/SoThredsApp.dir/map/MainAppMap.cpp.o
SoThredsApp: CMakeFiles/SoThredsApp.dir/threads/mapRender/MapRender.cpp.o
SoThredsApp: CMakeFiles/SoThredsApp.dir/threads/switch/SwitchThread.cpp.o
SoThredsApp: CMakeFiles/SoThredsApp.dir/threads/entity/Person.cpp.o
SoThredsApp: CMakeFiles/SoThredsApp.dir/threads/entityGenerator/EntityGenerator.cpp.o
SoThredsApp: CMakeFiles/SoThredsApp.dir/build.make
SoThredsApp: /usr/lib/x86_64-linux-gnu/libcurses.so
SoThredsApp: /usr/lib/x86_64-linux-gnu/libform.so
SoThredsApp: CMakeFiles/SoThredsApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable SoThredsApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SoThredsApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SoThredsApp.dir/build: SoThredsApp
.PHONY : CMakeFiles/SoThredsApp.dir/build

CMakeFiles/SoThredsApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SoThredsApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SoThredsApp.dir/clean

CMakeFiles/SoThredsApp.dir/depend:
	cd /home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wombat-laptop/GitLab/SO-project/SoThredsApp /home/wombat-laptop/GitLab/SO-project/SoThredsApp /home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug /home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug /home/wombat-laptop/GitLab/SO-project/SoThredsApp/cmake-build-debug/CMakeFiles/SoThredsApp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SoThredsApp.dir/depend

