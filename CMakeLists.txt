cmake_minimum_required(VERSION 3.21)
project(csci_473_stencil_serial C)

set(CMAKE_C_STANDARD 99)


#add_executable(csci_473_stencil_serial make-2d.c  utilities.c utilities.h)
#add_executable(csci_473_stencil_serial print-2d.c utilities.c utilities.h)
add_executable(csci_473_stencil_serial stencil-2d.c utilities.c utilities.h)
