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

set(CMAKE_CXX_STANDARD 23) # C++23

# Set the CMP0146 policy to NEW
if (POLICY CMP0146)
  cmake_policy(SET CMP0146 NEW)
endif()

# Set CUDA policies
if (POLICY CMP0104)
  cmake_policy(SET CMP0104 NEW)
endif()
if (POLICY CMP0105)
  cmake_policy(SET CMP0105 NEW)
endif()

find_package(CUDAToolkit)

if (CUDAToolkit_FOUND)
  message(STATUS "CUDA found")
  include_directories(${CUDAToolkit_INCLUDE_DIRS})
  include_directories(${CUDAToolkit_INCLUDE_DIRS}/include)

  message(STATUS "CUDA include dirs: ${CUDAToolkit_INCLUDE_DIRS}")
  message(STATUS "CUDA libraries: ${CUDAToolkit_LIBRARIES}")
  message(STATUS "CUDA version: ${CUDAToolkit_VERSION}")

  message(STATUS "Enabling CUDA")
  enable_language(CUDA)

  set(HAS_CUDA TRUE)
  add_definitions(-DCUDA_AVAILABLE=true)
else()
  message(STATUS "CUDA not found")
  set(HAS_CUDA FALSE)
endif()

if (HAS_CUDA)
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode arch=compute_75,code=sm_75")
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode arch=compute_86,code=sm_86")
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode arch=compute_86,code=compute_86")
  set(CMAKE_CUDA_COMPILE_OBJECT "${CMAKE_CUDA_COMPILE_OBJECT} -gencode arch=compute_75,code=sm_75")
  set(CMAKE_CUDA_COMPILE_OBJECT "${CMAKE_CUDA_COMPILE_OBJECT} -gencode arch=compute_86,code=sm_86")
  set(CMAKE_CUDA_COMPILE_OBJECT "${CMAKE_CUDA_COMPILE_OBJECT} -gencode arch=compute_86,code=compute_86")
endif()

project ("PhysInteractive")

add_subdirectory("MillerInc.PhysicsEngine")

# Add source to this project's executable.
add_executable (PhysInteractive "PhysInteractive.cpp" "PhysInteractive.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PhysInteractive PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(PhysInteractive PhysicsEngine)

# TODO: Add tests and install targets if needed.
