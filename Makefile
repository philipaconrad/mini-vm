SHELL = /bin/sh
SOURCES = types.h minivm.h minivm.c
CFLAGS += -Wall -Wextra

all: example

example: minivm.o
	$(CC) $(CFLAGS) -g example.c minivm.o -o example

lib: minivm.o
	ar rcs libminivm.a minivm.o

minivm.o:
	$(CC) $(CFLAGS) -g -c minivm.c -o minivm.o

bytecode.txt:
	python tools/bc.py "`cat tools/params.txt`" > bytecode.txt

clean:
	rm -f example *.o *.a *.txt

test: example bytecode.txt
	./example bytecode.txt

inspect: bytecode.txt
	od --format=u1 --width=4 bytecode.txt

sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)
