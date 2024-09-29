CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = s21_grep.c
OBJ = s21_grep.o
EXECUTABLE = s21_grep
HFILE = s21_grep.h

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE)
	rm -rf *.o

$(OBJ): $(SRC) $(HFILE)
	$(CC) -std=c11 -c $(CFLAGS) $(SRC) -c 

clean:
	rm -rf *.0 $(EXECUTABLE)

test: $(EXECUTABLE)
	./tests.sh

rebuild: make clean
	make all
