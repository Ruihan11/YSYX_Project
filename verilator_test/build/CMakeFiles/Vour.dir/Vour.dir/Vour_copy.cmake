# Verilated -*- CMake -*-
# DESCRIPTION: Verilator output: CMake include script with class lists
#
# This CMake script lists generated Verilated files, for including in higher level CMake scripts.
# This file is meant to be consumed by the verilate() function,
# which becomes available after executing `find_package(verilator).

### Constants...
set(PERL "perl" CACHE FILEPATH "Perl executable (from $PERL)")
set(VERILATOR_ROOT "/usr/local/share/verilator" CACHE PATH "Path to Verilator kit (from $VERILATOR_ROOT)")

### Compiler flags...
# User CFLAGS (from -CFLAGS on Verilator command line)
set(Vour_USER_CFLAGS )
# User LDLIBS (from -LDFLAGS on Verilator command line)
set(Vour_USER_LDLIBS )

### Switches...
# SystemC output mode?  0/1 (from --sc)
set(Vour_SC 0)
# Coverage output mode?  0/1 (from --coverage)
set(Vour_COVERAGE 0)
# Timing mode?  0/1
set(Vour_TIMING 0)
# Threaded output mode?  1/N threads (from --threads)
set(Vour_THREADS 1)
# VCD Tracing output mode?  0/1 (from --trace)
set(Vour_TRACE_VCD 0)
# FST Tracing output mode? 0/1 (from --trace-fst)
set(Vour_TRACE_FST 0)

### Sources...
# Global classes, need linked once per executable
set(Vour_GLOBAL "${VERILATOR_ROOT}/include/verilated.cpp" "${VERILATOR_ROOT}/include/verilated_threads.cpp")
# Generated module classes, non-fast-path, compile with low/medium optimization
set(Vour_CLASSES_SLOW "/home/ruihan11/Documents/YSYX_Project/verilator_test/build/CMakeFiles/Vour.dir/Vour.dir/Vour___024root__Slow.cpp" "/home/ruihan11/Documents/YSYX_Project/verilator_test/build/CMakeFiles/Vour.dir/Vour.dir/Vour___024root__DepSet_h637983f1__0__Slow.cpp")
# Generated module classes, fast-path, compile with highest optimization
set(Vour_CLASSES_FAST "/home/ruihan11/Documents/YSYX_Project/verilator_test/build/CMakeFiles/Vour.dir/Vour.dir/Vour.cpp" "/home/ruihan11/Documents/YSYX_Project/verilator_test/build/CMakeFiles/Vour.dir/Vour.dir/Vour___024root__DepSet_hf7027e39__0.cpp" "/home/ruihan11/Documents/YSYX_Project/verilator_test/build/CMakeFiles/Vour.dir/Vour.dir/Vour___024root__DepSet_h637983f1__0.cpp")
# Generated support classes, non-fast-path, compile with low/medium optimization
set(Vour_SUPPORT_SLOW "/home/ruihan11/Documents/YSYX_Project/verilator_test/build/CMakeFiles/Vour.dir/Vour.dir/Vour__Syms.cpp")
# Generated support classes, fast-path, compile with highest optimization
set(Vour_SUPPORT_FAST )
# All dependencies
set(Vour_DEPS "/usr/local/bin/verilator_bin" "/usr/local/share/verilator/include/verilated_std.sv" "our.v")
# User .cpp files (from .cpp's on Verilator command line)
set(Vour_USER_CLASSES )
