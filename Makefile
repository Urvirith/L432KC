# ARM GCC COMPILER CALL

# Toolchain To Use
TOOLCHAIN	:= arm-none-eabi-
CC		    := $(TOOLCHAIN)gcc		# C Compiler
AS			:= $(TOOLCHAIN)as		# Assembler
LD 			:= $(TOOLCHAIN)ld 		# Linker
OBJ 		:= $(TOOLCHAIN)objcopy	# Object Copy

# -Os				Optimize for Size
# -mcpu=cortex-m4	Compile for the ARM M4 Processor
# -mthumb			Target the MTHUMB Instruction Set
# -ftlo				Target the MTHUMB Instruction Set
ARCH 		:= m4
TARGET_ARCH := -mcpu=cortex-$(ARCH)
THUMB		:= -mthumb
LINKTIME	:= -flto
CFLAGS	  	:= -Os $(TARGET_ARCH) $(THUMB) #$(LINKTIME)
ASFLAGS		:= $(TARGET_ARCH) -mthumb
LDFLAGS 	:= -T 
OBJFLAGS	:= -O binary

SRC_DIR   := ./src
HAL_DIR   := $(SRC_DIR)/hal
I2C_DRI   := $(SRC_DIR)/driver/i2c
START_DIR := $(SRC_DIR)/startup
LINK_DIR  := $(SRC_DIR)/linker
OBJ_DIR	  := ./obj
BIN_DIR	  := ./bin

OBJS := $(OBJ_DIR)/common.o \
		$(OBJ_DIR)/timer.o \
		$(OBJ_DIR)/nvic.o \
		$(OBJ_DIR)/gpio.o \
		$(OBJ_DIR)/rcc.o \
		$(OBJ_DIR)/main.o

#	EXAMPLE OF AUTOMATIC VARIABLES
#	%.o: %.c %.h common.h
#		$(CC) $(CFLAGS) -c $<
#
#	$@ Looks at the target
#	(Target)
#	%.o: 			%.c %.h common.h
#	
#	$< Looks at the first source
#			(First Source)
#	%.o: 	%.c 					%.h common.h
#		$(CC) $(CFLAGS) -c $<
#	$^ Looks at the first source
#			(All Source)
#	%.o: 	%.c %.h common.h
#		$(CC) $(CFLAGS) -c $^
release: $(BIN_DIR)/main.bin

# Build An ELF 
$(BIN_DIR)/main.bin: $(BIN_DIR)/main.elf
	$(OBJ) $(OBJFLAGS) $^ $@

# Build An ELF 
$(BIN_DIR)/main.elf: $(LINK_DIR)/gcc_arm.ld $(OBJS) $(BIN_DIR)/startup.o
	$(LD) -Os -s $(LDFLAGS) $^ -o $@

# Build Dependances
$(BIN_DIR)/startup.o: $(START_DIR)/startup_ARMCM4.s
	$(AS) $< $(ASFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c  $< -o $@

$(OBJ_DIR)/%.o: $(I2C_DRI)/%.c $(I2C_DRI)/%.h $(HAL_DIR)/i2c.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(HAL_DIR)/%.c $(HAL_DIR)/%.h $(HAL_DIR)/common.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.elf
	rm -f $(BIN_DIR)/*.bin

flash:
	STM32_Programmer_CLI -c port=SWD -w $(BIN_DIR)/main.bin 0x08000000

info:
	STM32_Programmer_CLI -c port=SWD

reset:
	STM32_Programmer_CLI -c port=SWD -rst

hard_reset:
	STM32_Programmer_CLI -c port=SWD -hardRst

setup:
	mkdir obj
	mkdir bin

# To Move The Rules
#sudo cp ./rules/*.rules /etc/udev/rules.d/