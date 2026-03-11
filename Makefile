CC = gcc
CFLAGS = -Wall -O2 -std=c23 -Iinclude -fPIC
LIB_NAME = libcask
STATIC_LIB = $(LIB_NAME).a
SHARED_LIB = $(LIB_NAME).so
SRC_DIR = src
OBJ_DIR = build
INC_DIR = include/cask

TEST_BIN = build/test_runner

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(STATIC_LIB) $(SHARED_LIB)

build:
	mkdir -p $(OBJ_DIR)

$(STATIC_LIB): $(OBJS)
	ar rcs $@ $^

$(SHARED_LIB): $(OBJS)
	$(CC) -shared -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test
test: $(SHARED_LIB)
	$(CC) $(CFLAGS) tests/test.c -o tests/runner -L. -lcask
	@echo "Launching Test Runner..."
	@LD_LIBRARY_PATH=. ./tests/runner
	@rm ./tests/runner

install: all
	install -d /usr/local/include/cask
	install -m 644 $(INC_DIR)/*.h /usr/local/include/cask
	install -m 644 $(STATIC_LIB) /usr/local/lib
	install -m 755 $(SHARED_LIB) /usr/local/lib
	ldconfig

clean:
	rm -rf $(OBJ_DIR) $(STATIC_LIB) $(SHARED_LIB) tests/runner
