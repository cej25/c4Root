#########################################################
# Specify the name of the target executable

TARGETS:=s100

#########################################################
# Include common Makefile

include ../makefile_common.mk

PYTHON ?= python3
EXPERIMENT_CONFIG := ../../../config/s100/experiment.yaml
CONFIG_GENERATOR := ../../../scripts/validate_experiment.py
GENERATED_CONFIG := s100_config.gen.spec
GENERATED_FEBEX_BANKS := s100_febex_banks.gen.hh
SPEC_DEPENDENCIES := obj_s100/s100.spec.d

.PHONY: prepare_s100_spec
build_s100 test_s100: prepare_s100_spec

prepare_s100_spec: $(GENERATED_CONFIG) $(GENERATED_FEBEX_BANKS)
	@# UCESB caches spec includes. Regenerate dependencies from older checkouts.
	@if test -f "$(SPEC_DEPENDENCIES)" && \
	    grep -Fq 's100_whiterabbit.generated.spec' "$(SPEC_DEPENDENCIES)"; then \
	    rm -f "$(SPEC_DEPENDENCIES)"; \
	fi

$(GENERATED_CONFIG): CONFIG_MODE := --emit-s100-routing
$(GENERATED_FEBEX_BANKS): CONFIG_MODE := --emit-s100-febex-readers

$(GENERATED_CONFIG) $(GENERATED_FEBEX_BANKS): $(EXPERIMENT_CONFIG) $(CONFIG_GENERATOR)
	@tmp=$$(mktemp "$@.XXXXXX") || exit 1; \
	  trap 'rm -f "$$tmp"' EXIT; \
	  $(PYTHON) $(CONFIG_GENERATOR) $(CONFIG_MODE) $(EXPERIMENT_CONFIG) > "$$tmp" && mv -f "$$tmp" "$@"
