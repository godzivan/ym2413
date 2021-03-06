####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES:
.PHONY: all debug release clean

####################################################################
# Definitions                                                      #
####################################################################

DEVICE = EFM32GG332F1024
PROJECTNAME = ym2413

OBJ_DIR = build
EXE_DIR = exe
LST_DIR = lst

####################################################################
# Definitions of toolchain.                                        #
# You might need to do changes to match your system setup          #
####################################################################

# Change path to the tools according to your system configuration
# DO NOT add trailing whitespace chars, they do matter !
WINDOWSCS  ?= GNU Tools ARM Embedded\4.7 2012q4
LINUXCS ?= /home/joost/prj/arm/gcc-arm-embedded/gcc-arm-none-eabi-4_7-2013q3
SILABS := silabs
# eACommander is installed as part of Simplicity Studio
# it is required only to install the USB bootloader
EACOMMANDER := /home/joost/prj/silabs/eACommander/start-eACommander.sh

#LINKER_FILE := $(SILABS)/Device/EnergyMicro/EFM32GG/Source/GCC/efm32gg.ld 
LINKER_FILE := efm32gg_bootld.ld

USBTIMER := USB_TIMER3

# settings for xmodem based transfer
SERIAL := /dev/ttyACM0

RMDIRS     := rm -rf
RMFILES    := rm -rf
ALLFILES   := /*.*
NULLDEVICE := /dev/null
SHELLNAMES := $(ComSpec)$(COMSPEC)

# Try autodetecting the environment
ifeq ($(SHELLNAMES),)
  # Assume we are making on a Linux platform
  TOOLDIR := $(LINUXCS)
else
  QUOTE :="
  ifneq ($(COMSPEC),)
    # Assume we are making on a mingw/msys/cygwin platform running on Windows
    # This is a convenient place to override TOOLDIR, DO NOT add trailing
    # whitespace chars, they do matter !
    TOOLDIR := $(PROGRAMFILES)/$(WINDOWSCS)
    ifeq ($(findstring cygdrive,$(shell set)),)
      # We were not on a cygwin platform
      NULLDEVICE := NUL
    endif
  else
    # Assume we are making on a Windows platform
    # This is a convenient place to override TOOLDIR, DO NOT add trailing
    # whitespace chars, they do matter !
    SHELL      := $(SHELLNAMES)
    TOOLDIR    := $(ProgramFiles)/$(WINDOWSCS)
    RMDIRS     := rd /s /q
    RMFILES    := del /s /q
    ALLFILES   := \*.*
    NULLDEVICE := NUL
  endif
endif

# Create directories and do a clean which is compatible with parallell make
$(shell mkdir $(OBJ_DIR)>$(NULLDEVICE) 2>&1)
$(shell mkdir $(EXE_DIR)>$(NULLDEVICE) 2>&1)
$(shell mkdir $(LST_DIR)>$(NULLDEVICE) 2>&1)
ifeq (clean,$(findstring clean, $(MAKECMDGOALS)))
  ifneq ($(filter $(MAKECMDGOALS),all debug release),)
    $(shell $(RMFILES) $(OBJ_DIR)$(ALLFILES)>$(NULLDEVICE) 2>&1)
    $(shell $(RMFILES) $(EXE_DIR)$(ALLFILES)>$(NULLDEVICE) 2>&1)
    $(shell $(RMFILES) $(LST_DIR)$(ALLFILES)>$(NULLDEVICE) 2>&1)
  endif
endif

CC      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-gcc$(QUOTE)
CX      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-g++$(QUOTE)
LD      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-ld$(QUOTE)
AR      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-ar$(QUOTE)
OBJCOPY = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-objcopy$(QUOTE)
DUMP    = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-objdump$(QUOTE)

####################################################################
# Flags                                                            #
####################################################################

# -MMD : Don't generate dependencies on system header files.
# -MP  : Add phony targets, useful when a h-file is removed from a project.
# -MF  : Specify a file to write the dependencies to.
DEPFLAGS = -MMD -MP -MF $(@:.o=.d)

#
# Add -Wa,-ahld=$(LST_DIR)/$(@F:.o=.lst) to CFLAGS to produce assembly list files
#
override CFLAGS += -D$(DEVICE) -DUSB_TIMER=$(USBTIMER) -Wall -Wextra -mcpu=cortex-m3 -mthumb \
-mfix-cortex-m3-ldrd -ffunction-sections -fdata-sections -fomit-frame-pointer \
-DDEBUG_EFM_USER  $(DEPFLAGS)

CXFLAGS = -fno-exceptions -fno-rtti -std=gnu++11
CFLAGSEXTRA = -std=gnu99

override ASMFLAGS += -x assembler-with-cpp -D$(DEVICE) -Wall -Wextra -mcpu=cortex-m3 -mthumb

#
# NOTE: The -Wl,--gc-sections flag may interfere with debugging using gdb.
#

override LDFLAGS += -Xlinker -Map=$(LST_DIR)/$(PROJECTNAME).map -mcpu=cortex-m3 \
-mthumb -T$(LINKER_FILE) \
-Wl,--gc-sections

LIBS = -Wl,--start-group -lgcc -lc_s -lnosys   -Wl,--end-group

INCLUDEPATHS += \
-I. \
-I$(SILABS)/CMSIS/Include \
-I$(SILABS)/Device/EnergyMicro/EFM32GG/Include \
-I$(SILABS)/emlib/inc \
-I$(SILABS)/common/drivers \
-I$(SILABS)/common/bsp \
-I$(SILABS)/usb/inc \
-Iconfig \
-I$(SILABS)/reptile/glib

####################################################################
# Files                                                            #
####################################################################

C_SRC +=  \
$(SILABS)/Device/EnergyMicro/EFM32GG/Source/system_efm32gg.c \
$(SILABS)/common/drivers/udelay.c \
$(SILABS)/emlib/src/em_assert.c \
$(SILABS)/emlib/src/em_cmu.c \
$(SILABS)/emlib/src/em_emu.c \
$(SILABS)/emlib/src/em_ebi.c \
$(SILABS)/emlib/src/em_gpio.c \
$(SILABS)/emlib/src/em_int.c \
$(SILABS)/emlib/src/em_prs.c \
$(SILABS)/emlib/src/em_rtc.c \
$(SILABS)/emlib/src/em_system.c \
$(SILABS)/emlib/src/em_leuart.c \
$(SILABS)/emlib/src/em_i2c.c \
$(SILABS)/emlib/src/em_dma.c \
$(SILABS)/emlib/src/em_timer.c \
$(SILABS)/emlib/src/em_adc.c \
$(SILABS)/emlib/src/em_usart.c \
$(SILABS)/usb/src/em_usbd.c \
$(SILABS)/usb/src/em_usbdch9.c \
$(SILABS)/usb/src/em_usbhal.c \
$(SILABS)/usb/src/em_usbdep.c \
$(SILABS)/usb/src/em_usbdint.c \
$(SILABS)/usb/src/em_usbtimer.c

CX_SRC = adc0.cc clock.cc dma.cc event.cc led.cc leuart0.cc main.cc swd.cc \
         tick.cc timer0.cc usart0.cc usbcdc.cc ym.cc

s_SRC +=

S_SRC +=  \
$(SILABS)/Device/EnergyMicro/EFM32GG/Source/GCC/startup_efm32gg.S
#$(SILABS)/Device/EnergyMicro/EFM32GG/Source/G++/startup_efm32gg.S

####################################################################
# Rules                                                            #
####################################################################

C_FILES = $(notdir $(C_SRC) )
CX_FILES = $(notdir $(CX_SRC) )
S_FILES = $(notdir $(S_SRC) $(s_SRC) )
#make list of source paths, sort also removes duplicates
C_PATHS = $(sort $(dir $(C_SRC) ) )
S_PATHS = $(sort $(dir $(S_SRC) $(s_SRC) ) )

C_OBJS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o)) $(addprefix $(OBJ_DIR)/, $(CX_FILES:.cc=.o))
S_OBJS = $(if $(S_SRC), $(addprefix $(OBJ_DIR)/, $(S_FILES:.S=.o)))
s_OBJS = $(if $(s_SRC), $(addprefix $(OBJ_DIR)/, $(S_FILES:.s=.o)))
C_DEPS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.d)) $(addprefix $(OBJ_DIR)/, $(CX_FILES:.cc=.d))
OBJS = $(C_OBJS) $(S_OBJS) $(s_OBJS)

vpath %.c $(C_PATHS)
vpath %.s $(S_PATHS)
vpath %.S $(S_PATHS)

# Default build is release build
all:      release

debug:    CFLAGS += -DDEBUG -O0 -g
debug:    $(EXE_DIR)/$(PROJECTNAME).bin

release:  CFLAGS += -DNDEBUG -O3 
release:  $(EXE_DIR)/$(PROJECTNAME).bin

# Create objects from C SRC files
$(OBJ_DIR)/%.o: %.c
	@echo "Building file: $<"
	$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INCLUDEPATHS) -c -o $@ $<

# Create objects from C++ SRC files
$(OBJ_DIR)/%.o: %.cc
	@echo "Building file: $<"
	$(CX) $(CFLAGS) $(CXFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Assemble .s/.S files
$(OBJ_DIR)/%.o: %.s
	@echo "Assembling $<"
	$(CC) $(ASMFLAGS) $(INCLUDEPATHS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.S
	@echo "Assembling $<"
	$(CC) $(ASMFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Link
$(EXE_DIR)/$(PROJECTNAME).out: $(OBJS)
	@echo "Linking target: $@"
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(EXE_DIR)/$(PROJECTNAME).out

# Create binary file
$(EXE_DIR)/$(PROJECTNAME).bin: $(EXE_DIR)/$(PROJECTNAME).out
	@echo "Creating binary file"
	$(OBJCOPY) --verbose -O binary $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/$(PROJECTNAME).bin
	$(DUMP) -h -S -C $(EXE_DIR)/$(PROJECTNAME).out>$(LST_DIR)/$(PROJECTNAME)out.lst

clean:
ifeq ($(filter $(MAKECMDGOALS),all debug release),)
	$(RMDIRS) $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)
endif

# include auto-generated dependency files (explicit rules)
ifneq (clean,$(findstring clean, $(MAKECMDGOALS)))
-include $(C_DEPS)
endif

# upload via SWD
upload: exe/$(PROJECTNAME).bin
	$(EACOMMANDER) --flash $< -r

# upload via xmodem
xmodem: CFLAGS += -DNDEBUG -O3 -g
xmodem: exe/$(PROJECTNAME).bin
	# open serial device
	screen -d -m -S 'serial' $(SERIAL) 115200
	sleep 0.1
	# say we want to Upload
	screen -x "serial" -X eval '!!!| echo u'
	sleep 0.1
	# execute xmodem transfer
	screen -x "serial" -X eval 'exec !! sx -vv $<'
	sleep 2
	# say we want to Boot the installed firmware
	screen -x "serial" -X eval '!!!| echo b'

install-bootloader: usb_uart_bootloader-rom.bin
	$(EACOMMANDER) --flash $< -r
