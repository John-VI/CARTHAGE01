# Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

IDIR=includes
CC=gcc
CCFLAGS=-I$(IDIR) -ggdb -Wall -pedantic -fdiagnostics-color=always
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows -lpthread 
DEPS=clkwin.h clktex.h clkfont.h inputs.h monster.h grid.h player.h messaging.h
OBJ=main.o clkwin.o clktex.o clkfont.o inputs.o monster.o grid.o player.o messaging.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

test.exe: $(OBJ)
	$(CC) -o $@ $^ $(CCFLAGS) $(LIBS)

clean:
	rm *.o test.exe
