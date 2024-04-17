cmake_minimum_required(VERSION 3.0)

project("tensor" C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-g -std=c99 -Wall")

add_library(tensor tensor.c tensor_aux.c)
add_executable(sample sample.c)
target_link_libraries(sample tensor)
add_executable(tensor_test tensor_test.c)
target_link_libraries(tensor_test tensor)

# ## tests
add_test(test_new ./tensor_test "new")
add_test(test_zeros ./tensor_test "zeros")
add_test(test_ones ./tensor_test "ones")
add_test(test_copy ./tensor_test "copy")
add_test(test_get ./tensor_test "get")
add_test(test_size ./tensor_test "size")
add_test(test_element ./tensor_test "element")
add_test(test_add ./tensor_test "add")
add_test(test_mul ./tensor_test "mul")
add_test(test_equal ./tensor_test "equal")
add_test(test_sum ./tensor_test "sum")
add_test(test_max ./tensor_test "max")
add_test(test_reshape ./tensor_test "reshape")
add_test(test_flatten ./tensor_test "flatten")

# EOF
