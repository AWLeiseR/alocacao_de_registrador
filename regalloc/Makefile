CC=gcc
CFLAGS=
LIBS=

PROGRAMA = regalloc
EXEC = regalloc.c

$(PROGRAMA): $(EXEC)
	$(CC) -std=c99	regalloc.c $(LIBS) -o $(PROGRAMA)

clean:
	rm -f regalloc
