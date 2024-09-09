#!/bin/sh

# Disable LSan
# Drop into the debugger if Asan detects an error (abort_on_error=1)
export ASAN_OPTIONS=detect_leaks=0:abort_on_error=1
qemu-aarch64 -L /usr/aarch64-linux-gnu -g 9000 build/my_test
