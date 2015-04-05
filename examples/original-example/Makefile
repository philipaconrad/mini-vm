all: example

example:
	gcc -Wall -Wextra -g example.c ../../minivm.c -o example

bytecode.txt:
	python bc.py "[0,2,43,0,  3,2,0,0,  0,1,1,0,  0,0,0,0]" > bytecode.txt

test: example bytecode.txt
	./example bytecode.txt

inspect: bytecode.txt
	od --format=u1 --width=4 bytecode.txt

sloc:
	@$(foreach srcfile, $(SOURCES), printf "%-10s : %s\n" `cat $(srcfile) | grep . | wc -l` $(srcfile);)

clean:
	rm -f example *.txt
