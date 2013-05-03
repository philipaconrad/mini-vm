SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .o .lib .s

all: install

install:
	$(CC) -I. -I$(srcdir) $(CFLAGS) -g -c example.c -o mini-vm.exe

clean:
	rm mini-vm.exe
