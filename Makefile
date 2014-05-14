SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .h .c .o .lib .s
SOURCES = types.h minivm.h minivm.c
TEST_SOURCES = greatest.h
CFLAGS += -Wall -Wextra

all: build

build: minivm.o
	$(CC) $(CFLAGS) -g example.c minivm.o -o example
	ar rcs libminivm.a minivm.o

build-clang: minivm.o
	clang $(CFLAGS) -g example.c minivm.o -o example

minivm.o:
	$(CC) $(CFLAGS) -g -c minivm.c -o minivm.o

clean:
	rm -f example
	rm -f minivm.o
	rm -f bytecode.txt
	rm -f tools/bytecode.txt

test: build
	cd tools;            \
	./bcgen-erl.sh;      \
	cp bytecode.txt .. ; \
	cd .. ;
	./example bytecode.txt


CLANG_ANALYZER_EXISTS = @$(shell scan-build --version 2>/dev/null)
CPPCHECK_EXISTS       = @$(shell cppcheck --version 2>/dev/null)
analyze: clean
ifdef CLANG_ANALYZER_EXISTS
	@echo -e "\nclang-analyzer (scan-build) exists...\n"
	scan-build make
else
	@echo -e "clang-analyzer (scan-build) not found. Skipping...\n"
endif

ifdef CPPCHECK_EXISTS
	@echo -e "cppcheck exists...\n"
	$(shell cppcheck --enable=warning,performance . 2>&1)
else
	@echo -e "cppcheck not found. Skipping...\n"
endif


sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)
