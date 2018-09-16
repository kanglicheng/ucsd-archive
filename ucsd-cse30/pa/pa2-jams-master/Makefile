# Variables
OBJCOPY ?= objcopy
CXXFLAGS ?= -std=c++14 -Wall -Werror
PI_CC ?= $(CC)
PI_CXX ?= $(CXX)
PI_CFLAGS ?= $(CFLAGS)
PI_CXXFLAGS ?= $(CXXFLAGS)
PI_LD ?= $(LD)
PI_LDFLAGS ?= $(LDFLAGS)
PI_CONN := $(PI_HOST)
PI_AS ?= $(AS)
PI_OBJCOPY ?= $(OBJCOPY)
BUILD_SSH = $(1)

# Major targets
all: divmod.bin encrypt.bin decrypt.bin

%.s.o : %.s
	@$(call BUILD_SSH, $(PI_AS) $< -o $@)

%.bin : %.s.o
	@$(call BUILD_SSH, $(PI_OBJCOPY) -O binary $< $@)

clean:
	rm -f divmod.bin encrypt.bin decrypt.bin

.PHONY: all clean

