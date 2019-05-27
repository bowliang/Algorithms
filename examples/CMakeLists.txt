# Make sure the compiler can find include files from our Hello library. 
include_directories (${ALGORITHM_SOURCE_DIR}/src) 

# Make sure the linker can find the Hello library once it is built. 
link_directories (${ALGORITHM_BINARY_DIR}/src) 

set (ALGORITHM_EXAMPLES
math
utils
)

# iterate over tests
foreach (example ${ALGORITHM_EXAMPLES})

  # create executable
  add_executable(${example} EXCLUDE_FROM_ALL test_${example}.cpp)

  # link executable with the libraries
  target_link_libraries (${example} algorithm ${EXTERNAL_LIBS})

endforeach()


add_custom_target (examples DEPENDS ${ALGORITHM_EXAMPLES})
