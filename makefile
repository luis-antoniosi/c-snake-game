CC	:=	gcc
CCFLAGS	:=	-std=c11 -Wall -Wpedantic -Wextra -Werror -O3 -march=native
TARGET	:=	main
OBJS	:=	main.o game.o

.PHONY: all clean run

all: $(TARGET)

($TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c game.h
	$(CC) $(CCFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)