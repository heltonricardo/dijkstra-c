CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -I./fonte

TARGET = grafo

SOURCES = $(wildcard fonte/*.c)

HEADERS = $(wildcard fonte/*.h)

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) -lm

clean:
	rm -f $(TARGET)
