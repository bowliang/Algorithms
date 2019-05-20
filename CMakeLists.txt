# The name of our project is ALGORITHM. CMakeLists files in this project can 
# refer to the root source directory of the project as ${ALGORITHM_SOURCE_DIR}
# and to the root binary directory of the project as ${ALGORITHM_BINARY_DIR}

cmake_minimum_required (VERSION 2.6)
project (ALGORITHM)

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)

# check for compiler supporting C++11
check_cxx_compiler_flag (-std=c++0x HAVE_NEW_STD)
if (HAVE_NEW_STD)
  message (STATUS "*** INFO *** Compiler ${CMAKE_CXX_COMPILER} supports C++11 set of requirements.")
  add_definitions(-std=c++0x)
else()
  message(FATAL_ERROR "*** ERROR *** Compiler ${CMAKE_CXX_COMPILER} does not support the new standard. Set a different compmiler by using the cxx option to 'make config'.")
endif()  

# build shared library
message (STATUS "Building shared library")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  message (STATUS "*** INFO *** Setting -fPIC flag for position independent code.")
endif()

# verbose output
option (ALGORITHM_VERBOSE "Verbose output in algorithm library" OFF)
message (STATUS "Setting ALGORITHM_VERBOSE variable to ${ALGORITHM_VERBOSE}")

# add the binary tree to the search path for include files
include_directories(${PROJECT_BINARY_DIR} ${CPP_UTILS_INCLUDE})

# enable testing
enable_testing ()

add_subdirectory (src)
add_subdirectory (examples)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  ${ALGORITHM_SOURCE_DIR}/src/algorithm-config.hpp.in
  ${ALGORITHM_SOURCE_DIR}/src/algorithm-config.hpp
)



