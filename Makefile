CC = gcc
CFLAGS = -Wall -g -I./include
SRCS = src/main_test.c src/data_model.c
OBJS = $(SRCS:.c=.o)
TARGET = parser_test

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET) formatted_output.data
