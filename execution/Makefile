CC = gcc
CFLAGS = -Wall -g

# SRCS := $(wildcard *.c)
SRCS := ex.c
OBJS := $(SRCS:.c=.o)
TARGET := exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

