CXX=g++
CFLAGS=-g -std=c++11 -Wall -Wextra -Wwrite-strings -c
LFLAGS=-g

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)

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


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

#sim1: main.o Cell.o Entity.o User.o SensingTask.o Enviroment.o Game.o functions.o \
	${CXX} ${LFLAGS} -o sim1 main.o Cell.o Entity.o User.o SensingTask.o Enviroment.o Game.o functions.o\
\
main.o: main.cpp \
	${CXX} ${INCLUDES} ${CFLAGS} main.cpp\
\
Cell.o: Cell.cpp Cell.hpp\
	${CXX} ${INCLUDES} ${CFLAGS} Cell.cpp\
\
Entity.o: Entity.cpp Entity.hpp\
	${CXX} ${INCLUDES} ${CFLAGS} Entity.cpp\
\
User.o: User.cpp User.hpp\
	${CXX} ${INCLUDES} ${CFLAGS} User.cpp\
\
SensingTask.o: SensingTask.cpp SensingTask.hpp\
	${CXX} ${INCLUDES} ${CFLAGS} SensingTask.cpp\
\
Enviroment.o: Enviroment.cpp Enviroment.hpp\
	${CXX} ${INCLUDES} ${CFLAGS} Enviroment.cpp\
\
Game.o: Game.cpp Game.hpp\
	${CXX} ${INCLUDES} ${CFLAGS} Game.cpp\
\
functions.o: functions.hpp functions.cpp\
	${CXX} ${INCLUDES} ${CFLAGS} functions.cpp