CC = gcc
CFLAGS = -Wall -std=c99 -I./src
LDFLAGS = -lraylib -lasound -lopenal -lGL -lm -lpthread -ldl -lrt -lX11

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = buscaminas

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(EXEC) src/*.o
