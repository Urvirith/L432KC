  # the compiler: gcc for C program, define as g++ for C++
  CC = arm-none-eabi-gcc

  # compiler flags:
  #  -Os    			Optimizes for size
  #  -mcpu=cortex-m4	Targets the ARM M4 Processor
  #  -mthumb			Targets thumb instruction set
  CFLAGS  = -Os -mcpu=cortex-m4 -mthumb