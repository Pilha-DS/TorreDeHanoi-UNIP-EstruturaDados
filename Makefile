CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = hanoi
OBJS = main.o pilha.o hanoi.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c pilha.h hanoi.h
	$(CC) $(CFLAGS) -c main.c

pilha.o: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

hanoi.o: hanoi.c hanoi.h pilha.h
	$(CC) $(CFLAGS) -c hanoi.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
