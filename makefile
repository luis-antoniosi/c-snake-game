CC	:=	gcc
CFLAGS	:=	-std=c11 -Wall -Wpedantic -Wextra -Werror -O3 -march=native
TARGET	:=	main
OBJS	:=	main.o	game.o	utils.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c %.h 
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
