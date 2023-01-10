
export PROJECT_NAME := 01_led_blink # need user input project name
export PROJECT_FLAG := 0


# for sub directory
export SRC_AMSFILES :=
export SRC_C_FILES :=
export SRC_INCFILES :=
export SRC_CXX_FILES :=
export LINK_FILES :=


USE_USB = 0
USE_ALGO = 0
USE_DRV_ADC = 0
USE_DRV_CAN = 0
USE_DRV_DAC = 0
USE_DRV_PIN = 1
USE_DRV_HWTIMER = 0
USE_DRV_I2C = 0
USE_DRV_SPI = 0
USE_DRV_SERIAL = 1
USE_DRV_WDT = 0


include ../../path.mk

SRC_INCDIR := $(sort $(dir $(SRC_INCFILES)))

SRC_INCDIR += ./user/inc

SRC_C_FILES += $(foreach dir, ./user/src, $(wildcard $(dir)/*.c))
################################################################################################
TARGET           	?= main
OUTPUTDIR := 		output
###################################################COMPILE######################################
CROSS_COMPILE    	?= arm-none-eabi-

CC               	:= $(CROSS_COMPILE)gcc
CXX              	:= $(CROSS_COMPILE)g++
LD               	:= $(CROSS_COMPILE)ld
OBJCOPY          	:= $(CROSS_COMPILE)objcopy
OBJDUMP          	:= $(CROSS_COMPILE)objdump
SIZEINFO            := $(CROSS_COMPILE)size

#############################################################ARM################################
CPU           		:= -mcpu=cortex-m4
FPU        			:= -mfpu=fpv4-sp-d16
FLOAT_ABT 			:= -mfloat-abi=soft
ARM_INSTRUCTION 	:= -mthumb
MCU_FLAGS       	:= $(CPU) $(ARM_INSTRUCTION) $(FPU) $(FLOAT_ABT)

##################################################COMPILE_FLAGS#################################
C_COMPILE_FLAGS 	:= -lc -lm -lnosys -std=c11 -Wall -fdata-sections -ffunction-sections -g3 -gdwarf-2 -O0

CXX_COMPILE_FLAGS 	:= -lc -lm -lnosys -fno-rtti -std=c++11 -fno-exceptions -fno-builtin -Wall -fdata-sections -ffunction-sections -g3 -gdwarf-2 -O0

ASM_COMPILE_FLAGS 	:= -x assembler-with-cpp
#################################################################################################
EXTRA_LINK_FLAGS	:= -g -gdwarf-2 -lc -lm -lnosys -T$(LINK_FILES) -Wl,-Map=$(OUTPUTDIR)$(TARGET).map,--cref,--no-warn-mismatch -specs=nano.specs -specs=nosys.specs

#################################################################################################
DEFINE    := -DN32G4FR -DUSE_STDPERIPH_DRIVER
###############################################################
CFLAGS 				+= $(MCU_FLAGS) $(C_COMPILE_FLAGS) $(DEFINE)
CXXFLAGS 			+= $(MCU_FLAGS) $(CXX_COMPILE_FLAGS) $(DEFINE)
ASMFLAGS			+= $(MCU_FLAGS) $(ASM_COMPILE_FLAGS) $(DEFINE)

LFLAGS += $(MCU_FLAGS)  $(EXTRA_LINK_FLAGS)


PROFLAGS += -Wall  -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)"



INCLUDE 		 := $(patsubst %, -I%, $(SRC_INCDIR))
SFILES			 := $(SRC_AMSFILES)
CFILES			 := $(SRC_C_FILES)
CXXFILES         := $(SRC_CXX_FILES)

SFILENAME  		 := $(notdir $(SFILES))
CFILENAME 		 := $(notdir $(CFILES))
CXXFILENAME		 := $(notdir $(CXXFILES))

SOBJS		 	 := $(patsubst %, $(OUTPUTDIR)/%, $(SFILENAME:.s=.o))
COBJS		 	 := $(patsubst %, $(OUTPUTDIR)/%, $(CFILENAME:.c=.o))
CXXOBJS          := $(patsubst %, $(OUTPUTDIR)/%, $(CXXFILENAME:.cpp=.o))
OBJS			 := $(SOBJS) $(COBJS) $(CXXOBJS)

SRCDIRS          := $(dir $(SFILES)) $(dir $(CFILES)) $(dir $(CXXFILES))
VPATH			 := $(SRCDIRS)

OBJECTS = $(addprefix $(OUTPUTDIR)/,$(notdir $(CFILES:.c=.o)))
vpath %.c $(sort $(dir $(CFILES)))
# list of ASM program objects
OBJECTS += $(addprefix $(OUTPUTDIR)/,$(notdir $(SFILES:.s=.o)))
vpath %.s $(sort $(dir $(SFILES)))


# .PHONY: clean

all:  $(OUTPUTDIR)  $(OUTPUTDIR)/$(TARGET).elf


	
# $(OUTPUTDIR) $(OUTPUTDIR)/$(TARGET).elf

$(OUTPUTDIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@
	$(OBJCOPY) -O binary -S $(OUTPUTDIR)/$(TARGET).elf $(OUTPUTDIR)/$(TARGET).bin
	$(SIZEINFO) $@

$(OUTPUTDIR)/%.o: %.s
	$(CC)  $(ASMFLAGS) $(PROFLAGS) -c $^ -o $@

$(OUTPUTDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDE)  -g -gdwarf-2 -Wa,-a,-ad,-alms=$(OUTPUTDIR)/$(notdir $(<:.c=.lst))  $(PROFLAGS)  -o $@ $<

$(OUTPUTDIR):
	mkdir $@

clean:
	rm -rf $(OUTPUTDIR)/*
