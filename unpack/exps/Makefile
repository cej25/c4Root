# This Makefile is for software maintenance to test-build all
# experiment directories.  Users most likely just want to build the
# experiment they are interested in.

# Don't add any options in this Makefile, as they should go in each
# experiment directory!

#########################################################

ifeq (,$(UCESB_BASE_DIR))
TREE_OR_HOME_SRC_DIR = $(firstword $(wildcard $(addsuffix /$(1),$(shell pwd)/../../../ $(HOME))))
UCESB_BASE_DIR=$(call TREE_OR_HOME_SRC_DIR,ucesb)
endif
export UCESB_BASE_DIR

include $(UCESB_BASE_DIR)/makefile_direxist.inc

#########################################################

EXPS=s452 \
	beammonitor \
	lisa \
	s450 \
	NovTest \
	onlyFATIMA \
	s100 \
	s143 \
	s181 \
	bb7 \
	fimp \
	pareeksha \
	jikken \
	onlyBGO 
ALL_EXPS = $(EXPS)

#########################################################
# Rules for building experiments

.PHONY: all
all: build

#########################################################

# To be able to build in parallel, we must first ensure that any
# common dependencies are built, as each separate make invocation will
# not know about its cousins trying to rebuild the same prerequisite
# simultaneously.  Easiest is to just compile e.g. the 'empty'
# unpacker

empty_unpacker:
	+$(MAKE) -C $(UCESB_BASE_DIR) empty

#########################################################

define build_unpacker

.PHONY: $(1)
$(1): build_$(1)

.PHONY: build_$(1)
build_$(1): empty_unpacker
	$$(MAKE) -C $(1)

.PHONY: clean_$(1)
clean_$(1):
	$$(MAKE) -C $(1) clean

endef

$(foreach target,$(ALL_EXPS),$(eval $(call build_unpacker,$(target))))

BUILD_TARGETS=$(addprefix build_,$(ALL_EXPS))
CLEAN_TARGETS=$(addprefix clean_,$(ALL_EXPS))

#########################################################

.PHONY: build
build: $(BUILD_TARGETS)

.PHONY: clean
clean: $(CLEAN_TARGETS)

#########################################################
