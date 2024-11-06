# CMakeList.txt : CMake project for PhysInteractive, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.22)
project(PhysicsEngine LANGUAGES CXX)
# Set the compiler
#if (WIN32)
#  set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
#elseif (UNIX)
#  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#  endif()

  

# Set the C++ standard to the latest supported by the compiler

set(CMAKE_CXX_STANDARD 23) # C++23

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PhysInteractive")

# Add source to this project's executable.
add_executable (PhysInteractive "PhysInteractive.cpp" "PhysInteractive.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PhysInteractive PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
