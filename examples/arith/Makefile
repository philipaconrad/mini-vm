all: arith

arith:
	gcc -Wall -Wextra -g arith.c ../../minivm.c -o arith

bytecode.txt:
	python arithc.py "1 2 3 + + ?" > bytecode.txt

test: arith bytecode.txt
	./arith bytecode.txt

inspect: bytecode.txt
	od --format=u1 --width=4 bytecode.txt

sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)

clean:
	rm -f arith *.txt
