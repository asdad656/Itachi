# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lqf/cpp/Itachi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lqf/cpp/Itachi/build

# Include any dependencies generated for this target.
include src/Base/CMakeFiles/ITACHI_BASE.dir/depend.make

# Include the progress variables for this target.
include src/Base/CMakeFiles/ITACHI_BASE.dir/progress.make

# Include the compile flags for this target's objects.
include src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make

src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o: ../src/Base/src/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/config.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/config.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/config.cpp > CMakeFiles/ITACHI_BASE.dir/src/config.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/config.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/config.cpp -o CMakeFiles/ITACHI_BASE.dir/src/config.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o


src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o: ../src/Base/src/EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/EventLoop.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/EventLoop.cpp > CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/EventLoop.cpp -o CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o


src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o: ../src/Base/src/channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/channel.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/channel.cpp > CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/channel.cpp -o CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o


src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o: ../src/Base/src/epoll_poller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/epoll_poller.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/epoll_poller.cpp > CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/epoll_poller.cpp -o CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o


src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o: ../src/Base/src/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/logger.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/logger.cpp > CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/logger.cpp -o CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o


src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o: ../src/Base/src/threadpool_c++11.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/threadpool_c++11.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/threadpool_c++11.cpp > CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/threadpool_c++11.cpp -o CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o


src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o: src/Base/CMakeFiles/ITACHI_BASE.dir/flags.make
src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o: ../src/Base/src/timeStamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o -c /home/lqf/cpp/Itachi/src/Base/src/timeStamp.cpp

src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.i"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lqf/cpp/Itachi/src/Base/src/timeStamp.cpp > CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.i

src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.s"
	cd /home/lqf/cpp/Itachi/build/src/Base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lqf/cpp/Itachi/src/Base/src/timeStamp.cpp -o CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.s

src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.requires:

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.requires

src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.provides: src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.requires
	$(MAKE) -f src/Base/CMakeFiles/ITACHI_BASE.dir/build.make src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.provides.build
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.provides

src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.provides.build: src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o


# Object files for target ITACHI_BASE
ITACHI_BASE_OBJECTS = \
"CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o" \
"CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o" \
"CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o" \
"CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o" \
"CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o" \
"CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o" \
"CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o"

# External object files for target ITACHI_BASE
ITACHI_BASE_EXTERNAL_OBJECTS =

../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/build.make
../lib/libITACHI_BASE.so: src/Base/CMakeFiles/ITACHI_BASE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lqf/cpp/Itachi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library ../../../lib/libITACHI_BASE.so"
	cd /home/lqf/cpp/Itachi/build/src/Base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ITACHI_BASE.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Base/CMakeFiles/ITACHI_BASE.dir/build: ../lib/libITACHI_BASE.so

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/build

src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/config.cpp.o.requires
src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/EventLoop.cpp.o.requires
src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/channel.cpp.o.requires
src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/epoll_poller.cpp.o.requires
src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/logger.cpp.o.requires
src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/threadpool_c++11.cpp.o.requires
src/Base/CMakeFiles/ITACHI_BASE.dir/requires: src/Base/CMakeFiles/ITACHI_BASE.dir/src/timeStamp.cpp.o.requires

.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/requires

src/Base/CMakeFiles/ITACHI_BASE.dir/clean:
	cd /home/lqf/cpp/Itachi/build/src/Base && $(CMAKE_COMMAND) -P CMakeFiles/ITACHI_BASE.dir/cmake_clean.cmake
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/clean

src/Base/CMakeFiles/ITACHI_BASE.dir/depend:
	cd /home/lqf/cpp/Itachi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lqf/cpp/Itachi /home/lqf/cpp/Itachi/src/Base /home/lqf/cpp/Itachi/build /home/lqf/cpp/Itachi/build/src/Base /home/lqf/cpp/Itachi/build/src/Base/CMakeFiles/ITACHI_BASE.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Base/CMakeFiles/ITACHI_BASE.dir/depend

