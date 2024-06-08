PROTOC = protoc

CURR_DIR = $(shell pwd)
PROTO_PATH = $(CURR_DIR)/src/interface


PROTO_OUT = $(CURR_DIR)/.proto_out
OUT = $(CURR_DIR)/.out
CPP_LIB_OUT = $(CURR_DIR)/src/cpp/.out

SERVICE_PROBE_PATH = $(CURR_DIR)/src/python/service_probe
PYTHON_SRC_PATH = $(CURR_DIR)/src/python

PROTOS += $(wildcard $(PROTO_PATH)/*.proto)

C_EXTENSION_SO_NAME = zprobe.cpython-36m-x86_64-linux-gnu.so

# NO dependency, build everytime
all: c_extension_setup interfaces setup_file

c_extension_setup: c_extension
	@echo "\033[0;32m[SETUP]\033[m setup_zprobe.py"
	@python3 setup_zprobe.py  --quiet build_ext --inplace
	@if [ ! -d $(OUT) ]; then mkdir -p $(OUT); fi;
	@mv $(C_EXTENSION_SO_NAME) $(OUT)/


interfaces:
	@echo "\033[0;32m[GENERATE]\033[m Python bindings for proto files: " $(notdir $(PROTOS))
	@if [ ! -d $(PROTO_OUT) ]; then mkdir -p $(PROTO_OUT); fi;
	@$(PROTOC) -I=$(PROTO_PATH) \
          --python_out=$(PROTO_OUT) \
          $(PROTOS)

c_extension:
  # Simply call the Makefile inside the cpp src folder
  # TODO: include and share the same OUT/... folder
	@echo "\033[0;32m[SUB MODULE]\033[m cpp building"
	@make all -C $(CURR_DIR)/src/cpp

setup_file:
	@echo "\033[0;32m[GENERATE]\033[m setup.sh"
	@echo "export PYTHONPATH=$$PYTHONPATH:"$(OUT)":"$(PROTO_OUT)":"$(SERVICE_PROBE_PATH)":"$(PYTHON_SRC_PATH) > $(OUT)/setup.sh
	@echo "export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:"$(CPP_LIB_OUT) >> $(OUT)/setup.sh

clean:
	@echo "\033[0;32m[CLEAN UP]\033[m"
	@rm -rf $(PROTO_OUT)
	@rm -rf $(OUT)
	@rm -rf build
	@make clean -s -C $(CURR_DIR)/src/cpp

