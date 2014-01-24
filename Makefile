SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .o .lib .s
SOURCES = types.h minivm.h minivm.c
TEST_SOURCES = greatest.h
COMPILER = gcc -Wall -Wextra

all: build

build:
	$(COMPILER) $(CFLAGS) -g example.c $(SOURCES) -o example

clean:
	rm -f example
	rm -f bytecode.txt
	rm -f tools/bytecode.txt

test: build
	cd tools;            \
	./bcgen-erl.sh;      \
	cp bytecode.txt .. ; \
	cd .. ;
	./example bytecode.txt

sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)
