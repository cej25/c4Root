#########################################################
# Specify the name of the target executable

.DEFAULT_GOAL := s100
TARGETS:=s100

#########################################################
# Include common Makefile

include ../makefile_common.mk

PYTHON ?= python3
EXPERIMENT_CONFIG := ../../../config/s100/experiment.yaml
CONFIG_GENERATOR := ../../../scripts/validate_experiment.py
GENERATED_CONFIG := s100_config.gen.spec
SPEC_DEPENDENCIES := obj_s100/s100.spec.d

.PHONY: prepare_s100_spec
build_s100 test_s100: prepare_s100_spec

prepare_s100_spec: $(GENERATED_CONFIG)
	@# UCESB caches spec includes. Regenerate dependencies from older checkouts.
	@if test -f "$(SPEC_DEPENDENCIES)" && \
	    grep -Fq 's100_whiterabbit.generated.spec' "$(SPEC_DEPENDENCIES)"; then \
	    rm -f "$(SPEC_DEPENDENCIES)"; \
	fi

$(GENERATED_CONFIG): $(EXPERIMENT_CONFIG) $(CONFIG_GENERATOR)
	@tmp=$$(mktemp "$@.XXXXXX") || exit 1; \
	  trap 'rm -f "$$tmp"' EXIT; \
	  $(PYTHON) $(CONFIG_GENERATOR) --emit-s100-routing $(EXPERIMENT_CONFIG) > "$$tmp" && mv -f "$$tmp" "$@"
