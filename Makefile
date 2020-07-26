# Flags
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wwrite-strings

#if shared library target
#CFLAGS += -shared -undefined dynamic_lookup

TARGET_EXEC ?= sim1
BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS = $(INC_FLAGS) -MMD -MP -ggdb
CXXFLAGS = -std=c++14 -stdlib=libc++ 
LDFLAGS = -stdlib=libc++

all: $(TARGET_EXEC)

debug: CPPFLAGS += -DDEBUG 
debug: $(TARGET_EXEC)

test: test.out
test.out: $(OBJS) ./main2/main.o
	$(CXX) $(OBJS) ./main2/main.o -o $@ $(LDFLAGS)

# main target (C)
#$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
#	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# main target (C++)
$(TARGET_EXEC): $(OBJS) ./main1/main.o
	$(CXX) $(OBJS) ./main1/main.o -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

./main1/main.o: ./main1/main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./main1/main.cpp -o ./main1/main.o

./main2/main.o: ./main2/main.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./main2/main.cpp -o ./main2/main.o

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	rm -f sim1
	rm -f test.out
	rm -f data.txt
	rm -f ./main1/main.d
	rm -f ./main1/main.o
	rm -f ./main2/main.d
	rm -f ./main2/main.o

-include $(DEPS)

MKDIR_P ?= mkdir -p


.PHONY: run

run: $(BIN)
	./sim1