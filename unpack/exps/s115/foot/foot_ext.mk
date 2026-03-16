FOOT_PATH:=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))
FOOT_PATH:=$(patsubst %/,%,$(FOOT_PATH))

DPTC_PATH = $(FOOT_PATH)/dptc

CXXFLAGS += -I$(FOOT_PATH)
OBJS += dptc_unpack.o foot_ext.o foot_user.o
SRC_DIRS += $(FOOT_PATH)

$(OBJDIR)/dptc_unpack.o: $(DPTC_PATH)/dptc_unpack.c
	@echo "  DPTC   $@"
	$(QUIET)g++ -MMD -c -o $@ $<
