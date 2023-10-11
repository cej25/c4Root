USE_CERNLIB=1
USE_CURSES=1

#export USE_CERNLIB
export USE_CURSES

TREE_OR_HOME_SRC_DIR = $(firstword $(wildcard $(addsuffix /$(1),$(shell pwd)/../.. $(HOME))))

ifeq ($(UCESB_BASE_DIR),)
UCESB_BASE_DIR=$(call TREE_OR_HOME_SRC_DIR,ucesb)
export UCESB_BASE_DIR
endif

#CXX=g++-3.4
#export CXX

.PHONY: all
all: build

#########################################################
# Submakefiles that the programs depend on

include $(UCESB_BASE_DIR)/makefile_ucesbgen.inc
include $(UCESB_BASE_DIR)/makefile_psdc.inc

#########################################################

define build_rules

SPEC=$(firstword $(subst _, ,$(1)))
DEPENDENCIES=$(UCESB) $(PSDC) $(1).spec

$(1): build_$(1)

$(1).spec: $$(SPEC).spec
	@ln -s $$(SPEC).spec $(1).spec

.PHONY: build_$(1)
build_$(1): $$(DEPENDENCIES)
	@$$(MAKE) -f $$(UCESB_BASE_DIR)/makefile_unpacker.inc UNPACKER=$(1)

.PHONY: test_$(1)
test_$(1):
	$$(MAKE) -f $$(UCESB_BASE_DIR)/makefile_unpacker.inc UNPACKER=$(1) test

.PHONY: clean_$(1)
clean_$(1):
	$$(MAKE) -f $$(UCESB_BASE_DIR)/makefile_unpacker.inc UNPACKER=$(1) clean
	@[ ! -L $(1).spec ] || unlink $(1).spec

endef

define alias_rules
FROMTO:=$(subst ->, ,$(1))
FROM:=$(firstword $(subst ->, ,$(1)))
TO:=$(lastword $(subst ->, ,$(1)))

.PHONY: alias_$(1)
alias_$(1): $$(FROM)

$$(FROM): $$(TO)
	@echo "  LNK  $$(FROM) -> $$(TO)"
	@ln -s $$(TO) $$(FROM)

unalias_$(1):
	@echo " UNLNK $$(FROM) -> $$(TO)"
	@unlink $$(FROM)

endef

$(foreach target,$(TARGETS),$(eval $(call build_rules,$(target))))
$(foreach alias,$(ALIASES),$(eval $(call alias_rules,$(alias))))

BUILD_TARGETS=$(addprefix build_,$(TARGETS))
TEST_TARGETS=$(addprefix test_,$(TARGETS))
CLEAN_TARGETS+=$(addprefix clean_,$(TARGETS))
ALIAS_TARGETS=$(addprefix alias_,$(ALIASES))
UNALIAS_TARGETS=$(addprefix unalias_,$(ALIASES))

.PHONY: build
build: $(BUILD_TARGETS) aliases

.PHONY: test
test: $(TEST_TARGETS)

.PHONY: clean
clean: $(CLEAN_TARGETS) clean_aliases

.PHONY: aliases
aliases: $(ALIAS_TARGETS)

.PHONY: clean_aliases
clean_aliases: $(UNALIAS_TARGETS)

debug:
	@echo "UCSEB_BASE_DIR = $(UCESB_BASE_DIR)"
