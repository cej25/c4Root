PYTHON ?= python3
ROUTING_CONFIG := ../../../config/s100/experiment.yaml
ROUTING_GENERATOR := ../../../scripts/validate_experiment.py
ROUTING_INCLUDE := s100_whiterabbit.generated.spec

$(addprefix build_,$(TARGETS)) $(addprefix test_,$(TARGETS)): $(ROUTING_INCLUDE)

$(ROUTING_INCLUDE): $(ROUTING_CONFIG) $(ROUTING_GENERATOR)
	@tmp=$$(mktemp "$@.XXXXXX") || exit 1; \
	  trap 'rm -f "$$tmp"' EXIT; \
	  $(PYTHON) $(ROUTING_GENERATOR) --emit-s100-routing $(ROUTING_CONFIG) > "$$tmp" && mv -f "$$tmp" "$@"
