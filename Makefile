# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = "/mnt/c/storage/school/Computer Graphics/02 - Opdracht 2D L-Systemen/code"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/storage/school/Computer Graphics/02 - Opdracht 2D L-Systemen/code"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/mnt/c/storage/school/Computer Graphics/02 - Opdracht 2D L-Systemen/code/CMakeFiles" "/mnt/c/storage/school/Computer Graphics/02 - Opdracht 2D L-Systemen/code//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/mnt/c/storage/school/Computer Graphics/02 - Opdracht 2D L-Systemen/code/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named engine

# Build rule for target.
engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 engine
.PHONY : engine

# fast build rule for target.
engine/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/build
.PHONY : engine/fast

engine.o: engine.cc.o
.PHONY : engine.o

# target to build an object file
engine.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/engine.cc.o
.PHONY : engine.cc.o

engine.i: engine.cc.i
.PHONY : engine.i

# target to preprocess a source file
engine.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/engine.cc.i
.PHONY : engine.cc.i

engine.s: engine.cc.s
.PHONY : engine.s

# target to generate assembly for a file
engine.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/engine.cc.s
.PHONY : engine.cc.s

utils/easy_image.o: utils/easy_image.cc.o
.PHONY : utils/easy_image.o

# target to build an object file
utils/easy_image.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/easy_image.cc.o
.PHONY : utils/easy_image.cc.o

utils/easy_image.i: utils/easy_image.cc.i
.PHONY : utils/easy_image.i

# target to preprocess a source file
utils/easy_image.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/easy_image.cc.i
.PHONY : utils/easy_image.cc.i

utils/easy_image.s: utils/easy_image.cc.s
.PHONY : utils/easy_image.s

# target to generate assembly for a file
utils/easy_image.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/easy_image.cc.s
.PHONY : utils/easy_image.cc.s

utils/ini_configuration.o: utils/ini_configuration.cc.o
.PHONY : utils/ini_configuration.o

# target to build an object file
utils/ini_configuration.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/ini_configuration.cc.o
.PHONY : utils/ini_configuration.cc.o

utils/ini_configuration.i: utils/ini_configuration.cc.i
.PHONY : utils/ini_configuration.i

# target to preprocess a source file
utils/ini_configuration.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/ini_configuration.cc.i
.PHONY : utils/ini_configuration.cc.i

utils/ini_configuration.s: utils/ini_configuration.cc.s
.PHONY : utils/ini_configuration.s

# target to generate assembly for a file
utils/ini_configuration.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/ini_configuration.cc.s
.PHONY : utils/ini_configuration.cc.s

utils/l_parser.o: utils/l_parser.cc.o
.PHONY : utils/l_parser.o

# target to build an object file
utils/l_parser.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/l_parser.cc.o
.PHONY : utils/l_parser.cc.o

utils/l_parser.i: utils/l_parser.cc.i
.PHONY : utils/l_parser.i

# target to preprocess a source file
utils/l_parser.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/l_parser.cc.i
.PHONY : utils/l_parser.cc.i

utils/l_parser.s: utils/l_parser.cc.s
.PHONY : utils/l_parser.s

# target to generate assembly for a file
utils/l_parser.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/engine.dir/build.make CMakeFiles/engine.dir/utils/l_parser.cc.s
.PHONY : utils/l_parser.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... engine"
	@echo "... engine.o"
	@echo "... engine.i"
	@echo "... engine.s"
	@echo "... utils/easy_image.o"
	@echo "... utils/easy_image.i"
	@echo "... utils/easy_image.s"
	@echo "... utils/ini_configuration.o"
	@echo "... utils/ini_configuration.i"
	@echo "... utils/ini_configuration.s"
	@echo "... utils/l_parser.o"
	@echo "... utils/l_parser.i"
	@echo "... utils/l_parser.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

