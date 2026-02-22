CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O2 -Iheaders

OBJ_DIR := build

# Quellen
UNITY_SRC         := modules/unity/unity.c
TEST_MAIN         := tests/interpreter/test_interpreter.c
HELPER_TEST_MAIN  := tests/helpers/test_dyn_bytearray.c
ASSEMBLER_TEST_MAIN := tests/assembler/test_assembler.c
INTERPRETER_SRCS  := $(wildcard modules/interpreter/*.c)

# Aufteilen
INTERPRETER_LIB_SRCS := $(filter-out $(TEST_MAIN) $(UNITY_SRC), $(INTERPRETER_SRCS))

# Objektdateien im build/-Ordner
INTERPRETER_LIB_OBJS := $(patsubst modules/interpreter/%.c,$(OBJ_DIR)/%.o,$(INTERPRETER_LIB_SRCS))
UNITY_OBJ            := $(OBJ_DIR)/unity.o
TEST_OBJ             := $(OBJ_DIR)/test_interpreter.o
HELPER_TEST_OBJ      := $(OBJ_DIR)/test_dyn_bytearray.o
ASSEMBLER_TEST_OBJ   := $(OBJ_DIR)/test_assembler.o
ASSEMBLER_OBJ        := $(OBJ_DIR)/assembler.o

# helper code object (shared by tests and later modules)
DYN_OBJ              := $(OBJ_DIR)/dyn_bytearray.o

TARGET ?= test_interpreter

# Additional binary for helper tests
HELPER_TEST_BIN := test_dyn_bytearray

.PHONY: all clean test

all: $(TARGET) $(HELPER_TEST_BIN) assembler_test

# run both test executables
test: $(TARGET) $(HELPER_TEST_BIN) assembler_test
	./$(TARGET)
	./$(HELPER_TEST_BIN)
	./assembler_test

$(TARGET): $(INTERPRETER_LIB_OBJS) $(UNITY_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(HELPER_TEST_BIN): $(UNITY_OBJ) $(HELPER_TEST_OBJ) $(DYN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

assembler_test: $(UNITY_OBJ) $(ASSEMBLER_TEST_OBJ) $(DYN_OBJ) $(ASSEMBLER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Allgemeine Regel für Interpreter-Quellen
$(OBJ_DIR)/%.o: modules/interpreter/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regel für verschobene Tester
$(OBJ_DIR)/test_interpreter.o: tests/interpreter/test_interpreter.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(UNITY_OBJ): $(UNITY_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): $(TEST_MAIN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(HELPER_TEST_OBJ): $(HELPER_TEST_MAIN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASSEMBLER_TEST_OBJ): $(ASSEMBLER_TEST_MAIN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DYN_OBJ): modules/helpers/dyn_bytearray.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASSEMBLER_OBJ): modules/assembler/assembler.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET) $(HELPER_TEST_BIN) assembler_test