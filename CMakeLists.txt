cmake_minimum_required(VERSION 3.24)
project(5vm C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE 5VM_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_library(5vm ${5VM_SRC})
target_include_directories(5vm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE 5VM_BIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/bin/*.c)
add_executable(5vm_bin ${5VM_BIN_SRC})
target_link_libraries(5vm_bin 5vm)

add_executable(5vm_test test/test_vm.c)
target_link_libraries(5vm_test 5vm)

