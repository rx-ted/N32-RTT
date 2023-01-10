
# necessary folders
CURRENT_SRC_DIR += $(RTT_ROOT)/include
CURRENT_SRC_DIR += $(RTT_ROOT)/include/libc
CURRENT_SRC_DIR += $(RTT_ROOT)/src
CURRENT_SRC_DIR += $(RTT_ROOT)/libcpu/cortex-m4
CURRENT_SRC_DIR += $(RTT_ROOT)/components/drivers/src
# CURRENT_SRC_DIR += $(RTT_ROOT)/components/drivers/misc
CURRENT_SRC_DIR += $(RTT_ROOT)/components/drivers/include
CURRENT_SRC_DIR += $(RTT_ROOT)/components/drivers/include/drivers
CURRENT_SRC_DIR += $(RTT_ROOT)/components/drivers/include/ipc


SRC_C_FILES += $(foreach dir, $(CURRENT_SRC_DIR), $(wildcard $(dir)/*.c))
SRC_C_FILES += $(RTT_ROOT)/components/drivers/misc/pin.c
SRC_INCFILES += $(foreach dir, $(CURRENT_SRC_DIR), $(wildcard $(dir)/*.h))
SRC_CXX_FILES += $(foreach dir, $(CURRENT_SRC_DIR), $(wildcard $(dir)/*.cpp))
LINK_FILES += $(foreach dir, $(CURRENT_SRC_DIR), $(wildcard $(dir)/*.ld))
SRC_AMSFILES +=  $(foreach dir, $(CURRENT_SRC_DIR), $(wildcard $(dir)/*_gcc.s))


