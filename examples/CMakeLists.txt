# CMakeLists for the cross section libary

include_directories(${CMAKE_SOURCE_DIR}/include ${ROOT_INCLUDE_DIR})

# Executable for an example program that links against ROOT
add_executable(example_root_program example_root_program.cpp)
target_link_libraries(example_root_program ${ROOT_LIBRARIES} )
