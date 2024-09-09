project(test_project_dev_with_qemu)

set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

enable_testing()
add_executable(my_test test.cc)

target_compile_options(my_test PRIVATE -g -fsanitize=address,undefined)
target_link_libraries(my_test PRIVATE asan ubsan)

add_test(NAME my_test COMMAND env ASAN_OPTIONS=detect_leaks=0:abort_on_error=1 qemu-aarch64 -L /usr/aarch64-linux-gnu ${CMAKE_CURRENT_BINARY_DIR}/my_test)
