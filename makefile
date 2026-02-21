CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O2 -Iheaders

OBJ_DIR := build

# Quellen
UNITY_SRC  := modules/unity/unity.c
TEST_MAIN  := modules/interpreter/test_interpreter.c
INTERPRETER_SRCS := $(wildcard modules/interpreter/*.c)

# Aufteilen
INTERPRETER_LIB_SRCS := $(filter-out $(TEST_MAIN) $(UNITY_SRC), $(INTERPRETER_SRCS))

# Objektdateien im build/-Ordner
INTERPRETER_LIB_OBJS := $(patsubst modules/interpreter/%.c,$(OBJ_DIR)/%.o,$(INTERPRETER_LIB_SRCS))
UNITY_OBJ            := $(OBJ_DIR)/unity.o
TEST_OBJ             := $(OBJ_DIR)/test_interpreter.o

TARGET ?= test_interpreter

.PHONY: all clean test

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(INTERPRETER_LIB_OBJS) $(UNITY_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Allgemeine Regel für Interpreter-Quellen
$(OBJ_DIR)/%.o: modules/interpreter/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(UNITY_OBJ): $(UNITY_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): $(TEST_MAIN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)