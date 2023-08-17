echo "Writing build_type..."

echo "#ifndef BUILD_TYPE_H
#define BUILD_TYPE_H

#define HARDWARE_BUILD

#endif" > core/build_type.h
echo "Writing makefile..."
echo "TARGET ?= picos
SRC_DIRS ?= ./src ./core ./os ./apps

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LDFLAGS = -lwiringPi
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -O3 -Wall -Wextra -Werror -pedantic
CC = clang

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

test:
	./$(TARGET)

-include $(DEPS)" > Makefile
echo "Done configuring environment for HARDWARE_BUILD"
