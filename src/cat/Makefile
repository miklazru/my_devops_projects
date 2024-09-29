CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = s21_cat.c
OBJ = s21_cat.o
EXECUTABLE = s21_cat
HFILE = s21_cat.h

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE)
	rm -rf *.o

$(OBJ): $(SRC) $(HFILE)
	$(CC) -std=c11 -c $(CFLAGS) $(SRC) -c 

clean:
	rm -rf *.0 $(EXECUTABLE)

rebuild: make clean
	make all
