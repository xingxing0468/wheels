CXX = g++
PROTOC = protoc

PROTO_OUT = $(CURR_DIR)/.proto_out
OUT = $(CURR_DIR)/.out

CURR_DIR = $(shell pwd)
PROTO_PATH = $(CURR_DIR)/../interface

PROTOS += $(wildcard $(PROTO_PATH)/*.proto)

SRC += $(wildcard *.cpp)
SRC += $(wildcard service_implementation/*.cpp)
SRC += $(wildcard utils/*.cpp)

# .proto generated sources
SRC += $(patsubst %.proto, %.pb.cc, $(addprefix $(PROTO_OUT)/, $(notdir $(PROTOS))))

INC += $(CURR_DIR)
INC += $(PROTO_OUT)

LIBS += protobuf

TARGET = libzprobe_impl.so

FLAGS += -DNDEBUG -g -fPIC -shared -std=c++11

MAJOR_VERSION = 1
MINOR_VERSION = 0

# TESTS
TEST_OUT = $(CURR_DIR)/.test_out

G_TEST_PATH = /usr/src/googletest/googletest

G_TEST_SRC += gtest-all.cc
G_TEST_SRC += gtest_main.cc

#G_TEST_INPUTS = $(addprefix $(G_TEST_PATH)/src/, $(G_TEST_SRC))
G_TEST_OBJS = $(addprefix $(TEST_OUT)/, $(patsubst %.cc, %.o, $(G_TEST_SRC)))
vpath %cc /usr/src/googletest/googletest/src/

TEST_TARGET = $(TEST_OUT)/test

TEST_SRCS += $(wildcard unit_tests/*.cpp)

# NO dependency, build everytime
all: interfaces
	@echo "\033[0;32m[BUILD]\033[m " $(notdir $(SRC))
	@if [ ! -d $(OUT) ]; then mkdir -p $(OUT); fi;
	@$(CXX)  \
          -DMAJOR_VERSION=$(MAJOR_VERSION) -DMINOR_VERSION=$(MINOR_VERSION) \
          $(SRC) \
          $(FLAGS) \
          $(addprefix -I, $(INC)) \
          $(addprefix -l, $(LIBS)) \
          -o $(OUT)/$(TARGET)

# NO dependency, build everytime
interfaces:
	@echo "\033[0;32m[GENERATE]\033[m cpp bindings for proto files: " $(notdir $(PROTOS))
	@if [ ! -d $(PROTO_OUT) ]; then mkdir -p $(PROTO_OUT); fi;
	@$(PROTOC) -I=$(PROTO_PATH) \
          --cpp_out=$(PROTO_OUT) \
          $(PROTOS)

clean:
	@echo "\033[0;32m[CLEAN UP]\033[m"
	@rm -rf $(PROTO_OUT)
	@rm -rf $(OUT)
	@rm -rf $(TEST_OUT)


# NO dependency, build everytime
test: $(G_TEST_OBJS) interfaces
	@echo "\033[0;32m[BUILDING TEST]\033[m " $(notdir $(TEST_SRCS))
	@if [ ! -d $(TEST_OUT) ]; then mkdir -p $(TEST_OUT); fi;
	@$(CXX) \
          $(TEST_SRCS) \
          $(SRC) \
          $(G_TEST_OBJS) \
          $(addprefix -I, $(INC)) \
          $(addprefix -l, $(LIBS)) -lpthread \
         -o $(TEST_TARGET)
	@echo "[RUNNING TEST]"
	@$(TEST_TARGET)

# GTEST obj files
$(TEST_OUT)/%.o: %.cc
	@echo "\033[0;32m[COMPILE]\033[m " $(notdir $<)
	@if [ ! -d $(TEST_OUT) ]; then mkdir -p $(TEST_OUT); fi;
	@$(CXX) \
          -I$(G_TEST_PATH) \
          -g -DGTEST_HAS_PTHREAD=0 \
          -c $< \
          -o $@
