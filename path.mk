
SUBMAKE_NAME = submake.mk

export ROOT = ../..
export DRIVERS_ROOT = $(ROOT)/drivers
export LIBRARIES_ROOT = $(ROOT)/libraries
export RTT_ROOT = $(ROOT)/rt-thread

# bsp 
BSP_ROOT = $(ROOT)/bsp
PROJECT_ROOT = $(BSP_ROOT)/$(PROJECT_NAME)


# Walk through the folders
include $(DRIVERS_ROOT)/$(SUBMAKE_NAME)
include $(LIBRARIES_ROOT)/$(SUBMAKE_NAME)
include $(RTT_ROOT)/$(SUBMAKE_NAME)

