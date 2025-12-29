CC = gcc
CFLAGS = -Wall -g -I./include
LIB_SRCS = src/parser_csvtodata.c
TEST_SRCS = examples/simple_test.c
TARGET_LIB = libfann_csv.a
TARGET_TEST = fann_csv_test

.PHONY: all clean

all: $(TARGET_TEST)


$(TARGET_TEST): $(TEST_SRCS) $(LIB_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET_TEST) $(TARGET_LIB) *.o src/*.o examples/*.o new_formatted_output.data
