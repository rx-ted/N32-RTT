# kernel library 


STARTUP_DIR := $(LIBRARIES_ROOT)/startup

CMSIS_DIR := $(LIBRARIES_ROOT)/CMSIS
C_DIRS += $(CMSIS_DIR)/src
INC_DIRS += $(CMSIS_DIR)/inc

HAL_DIR := $(LIBRARIES_ROOT)/n32g4fr_hal
C_DIRS += $(HAL_DIR)/src
INC_DIRS += $(HAL_DIR)/inc
LIB_DIRS += $(HAL_DIR)/inc

ifeq ($(USE_USB),1)
	USB_DIR := $(LIBRARIES_ROOT)/n32g4fr_usbfs_driver
	INC_DIRS += $(USB_DIR)/inc
	C_DIRS += $(USB_DIR)/src
endif

ifeq ($(USE_ALGO),1)
	ALGO_DIR := $(LIBRARIES_ROOT)/n32g4fr_algo_lib
	INC_DIRS += $(ALGO_DIR)/inc
	LIB_DIRS += $(ALGO_DIR)/lib
endif

SRC_AMSFILES += $(STARTUP_DIR)/startup_n32g4fr_gcc.s
LINK_FILES += $(STARTUP_DIR)/n32g4fr_flash.ld
SRC_C_FILES += $(foreach dir, $(C_DIRS), $(wildcard $(dir)/*.c))
SRC_INCFILES += $(foreach dir, $(INC_DIRS), $(wildcard $(dir)/*.h))
SRC_LIB_FILES += $(foreach dir, $(LIB_DIRS), $(wildcard $(dir)/*.lib))

