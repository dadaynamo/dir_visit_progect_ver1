CC=gcc

SRC=script.c

CFLAGS = -Wall -Wextra

OBJ=$(SRC:.c=.o)

EXEC=applicativo

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) -lm

clean:
	rm -f *.o

test1:
	bash ./script.sh .

test2:
	./applicativo .

.PHONY: test1 test2 clean
