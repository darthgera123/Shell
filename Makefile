IDIR = include/
CC=gcc
CFLAGS=-I$(IDIR)

SRCDIR =src

ODIR=obj

_DEPS = shellFunctions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = mainLoop.o shell.o prompt.o ls.o commands.o pinfo.o echo.o cd.o pwd.o \
		exit.o exitHandler.o newPointer.o run.o clock.o bgKiller.o pipeShell.o \
		getJobNum.o overkillShell.o fgShell.o killJobShell.o setenvShell.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 