# find all source files to build the library
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} ALGORITHM_LIB_SRC)
list(REMOVE_ITEM ALGORITHM_LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# add library algorithm
add_library (algorithm ${ALGORITHM_LIB_SRC})

# link library with other libraries
target_link_libraries (algorithm ${EXTERNAL_LIBS})

# specify installation of the library and the header files
install (TARGETS algorithm DESTINATION lib)
file(GLOB HEADER_FILES ${PROJECT_CURRENT_SOURCE_DIR} "*.hpp")
install (FILES  ${HEADER_FILES} DESTINATION include/algorithm)

# add executable
add_executable(a.out main.cpp)

# link executable
target_link_libraries (a.out
algorithm
${EXTERNAL_LIBS}
)


