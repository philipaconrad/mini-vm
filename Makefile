SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .o .lib .s
MINIVM_SOURCES = types.h minivm.h minivm.c

all: install

install:
	$(CC) -I. -I$(srcdir) $(CFLAGS) -g example.c $(MINIVM_SOURCES) -o mini-vm.exe

clean:
	rm mini-vm.exe
