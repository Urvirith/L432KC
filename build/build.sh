arm-none-eabi-gcc -c -Os -mcpu=cortex-m4 -mthumb -o main.o  ../src/main.c
arm-none-eabi-as startup_ARMCM4.S -mcpu=cortex-m4 -mthumb -g -o startup.o
arm-none-eabi-ld -T gcc_arm.ld main.o startup.o -o main.elf
arm-none-eabi-objcopy -O binary main.elf main.bin
