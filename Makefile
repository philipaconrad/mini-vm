SHELL = /bin/sh
SOURCES = minivm.h minivm.c
CFLAGS += -Wall -Wextra

lib: minivm.o
	ar rcs libminivm.a minivm.o

minivm.o:
	$(CC) $(CFLAGS) -g -c minivm.c -o minivm.o

clean:
	rm -f *.o *.a *.txt

inspect: bytecode.txt
	od --format=u1 --width=4 bytecode.txt

sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)
