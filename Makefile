CC=gcc
CFLAGS=-g -Wall -Wstrict-prototypes -std=gnu99
LFLAGS=-lm
all: make-2d print-2d stencil-2d

# EXECUTABLES
make-2d: make-2d.o utilities.o
	$(CC) $(LFLAGS) -o make-2d ./make-2d.o ./utilities.o
print-2d: print-2d.o utilities.o
	$(CC) $(LFLAGS) -o printf-2d ./print-2d.o ./utilities.o
stencil-2d: stencil-2d.o utilities.o
	$(CC) $(LFLAGS) -o stencil-2d ./stencil-2d.o ./utilities.o

# BASE EXECUTABLES - OBJECT FILES
make-2d.o: make-2d.c utilities.h
	$(CC) $(CFLAGS) -c ./make-2d.c ./utilities.h
print-2d.o: print-2d.c utilities.h
	$(CC) $(CFLAGS) -c ./print-2d.c ./utilities.h
stencil-2d.o: stencil-2d.c utilities.h
	$(CC) $(CFLAGS) -c ./stencil-2d.c ./utilities.h

# BASE FILES - FUNCTION SOURCE FILES
utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) -c ./utilities.c ./utilities.h

# MISC COMMANDS
clean:
	rm -f *.o core* *.h.gch *.out make-2d print-2d stencil-2d