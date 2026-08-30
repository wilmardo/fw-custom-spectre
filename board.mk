include $(BOARD_DIR)/firmware/firmware.mk


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

# this would save some flash while being unable to update WBO controller firmware
DDEFS += -DEFI_WIDEBAND_FIRMWARE_UPDATE=FALSE

# disabled: current ext/rusefi mass-storage ramdisk code (hw_layer/mass_storage/mass_storage_init.cpp)
# fails to build with GCC 13 ("duplicate 'static' specifier" on the RamDisk instance) - unrelated to
# SPECTRE's pins, this is an upstream build issue. fw-custom-paralela disables the same feature.
DDEFS += -DEFI_EMBED_INI_MSD=FALSE

# assign critical LED to a non-existent pin if you do not have it on your board
# good old PD14 is still the default value
# DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::I15

# EGT chip
#un-comment to enable
#DDEFS += -DEFI_MAX_31855=TRUE

#see main repo for details on this any many other optional subsystems. We have too many, one has to choose what fits into his choice of stm32
#DDEFS += -DEFI_ONBOARD_MEMS=TRUE
