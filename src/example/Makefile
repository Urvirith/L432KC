# ARM GCC COMPILER CALL
CC		    := arm-none-eabi-gcc	# c compiler
AS			:= arm-none-eabi-as		# assembler
LD 			:= arm-none-eabi-ld 	# linker
# -Os				Optimize for Size
# -mcpu=cortex-m4	Compile for the ARM M4 Processor
# mthumb			Target the MTHUMB Instruction Set
CFLAGS	  	:= -Os -mcpu=cortex-m4 -mthumb
ASFLAGS		:= -mcpu=cortex-m4 -mthumb
LDFLAGS 	:= -T 

SRC_DIR   := ./src
HAL_DIR   := ./src/hal
I2C_DRI   := ./src/driver/i2c
BUILD_DIR := ./build

PROJECT = main

OBJ = obj/
# OBJS: list of object files
OBJS = common.o \
			gpio.o \
				i2c.o \
					rcc.o \
						timer.o \
							usart.o \
								fxas21002.o \
									fxos8700.o \
										startup_ARMCM4.o 

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

# Rules to build bin
all: bin/$(PROJECT).bin

# Final Build Step
bin/$(PROJECT).bin: bin/$(PROJECT).elf
	$(OBJCOPY)-O binary $< $@

# Build An ELF 
bin/$(PROJECT).elf: $(OBJ)main.o $(OBJ)startup_ARMCM4.o $(BUILD_DIR)/gcc_arm.ld
	$(LD) $(LDFLAGS) $< -o $@


#$(OBJ_DIR)embed.o: $(OBJ_DIR)%.o
#	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)%.o: $(BUILD_DIR)/%.S
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ)%.o: $(I2C_DRI)/%.c $(I2C_DRI)/%.h $(HAL_DIR)/i2c.h
	$(CC) $(CFLAGS) -c $< 

$(OBJ)%.o: $(HAL_DIR)/%.c $(HAL_DIR)/%.h $(HAL_DIR)/common.h
	$(CC) $(CFLAGS) -c $< 

$(OBJ)%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f $(OBJ_DIR)*.o