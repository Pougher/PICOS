TARGET ?= picos
SRC_DIRS ?= ./src ./core

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LDFLAGS = -lSDL2 -L/opt/homebrew/Cellar/sdl2/2.26.4/lib
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -O3 -Wall -Wextra -Werror -pedantic -I/opt/homebrew/Cellar/sdl2/2.26.4/include

CC = clang

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

test:
	./$(TARGET)

-include $(DEPS)
