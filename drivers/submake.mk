
# device add some drivers
ifeq ($(USE_DRV_ADC),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_adc.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_adc.h
endif

ifeq ($(USE_DRV_CAN),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_can.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_can.h
endif

ifeq ($(USE_DRV_DAC),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_dac.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_dac.h
endif
ifeq ($(USE_DRV_PIN),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_gpio.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_gpio.h
endif
ifeq ($(USE_DRV_HWTIMER),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_hwtimer.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_hwtimer.h
endif
ifeq ($(USE_DRV_I2C),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_i2c.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_i2c.h
endif
ifeq ($(USE_DRV_SPI),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_spi.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_spi.h
endif

ifeq ($(USE_DRV_SERIAL),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_usart.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_usart.h
endif
ifeq ($(USE_DRV_WDT),1)
	SRC_C_FILES += $(DRIVERS_ROOT)/drv_wdt.c
	SRC_INCFILES += $(DRIVERS_ROOT)/drv_wdt.h
endif

