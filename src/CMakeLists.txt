# Specify the version being used as well as the language
cmake_minimum_required(VERSION 2.6)

# Name your project here
project(modules)

# Compiler flags
link_libraries(fftw3f m)

# This tells CMake to fib.c and name it fibonacci
add_executable(sqfft sqfft.c )
add_executable(sqpower sqpower.c)
add_executable(sqread sqread.c)
add_executable(sqsamples sqsamples.c)
add_executable(sqsum sqsum.c)
add_executable(sqwindow sqwindow.c)
