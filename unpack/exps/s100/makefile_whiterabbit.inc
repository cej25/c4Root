PYTHON ?= python3
WR_CONFIG := ../../../config/s100/experiment.yaml
WR_GENERATOR := ../../../scripts/validate_experiment.py
WR_INCLUDE := s100_whiterabbit.generated.spec

$(addprefix build_,$(TARGETS)) $(addprefix test_,$(TARGETS)): $(WR_INCLUDE)

$(WR_INCLUDE): $(WR_CONFIG) $(WR_GENERATOR)
	@tmp=$$(mktemp "$@.XXXXXX") || exit 1; \
	  trap 'rm -f "$$tmp"' EXIT; \
	  $(PYTHON) $(WR_GENERATOR) --emit-whiterabbit $(WR_CONFIG) > "$$tmp" && mv -f "$$tmp" "$@"
