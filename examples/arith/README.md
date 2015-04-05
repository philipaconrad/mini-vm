RPN Calculator
--------------

This example program consists of two parts: A compiler and a bytecode interpreter.

The compiler (`arithc.py`) is written in Python and turns simple postfix mathematical expressions into bytecode for the interpreter.

The bytecode interpreter (`arith`) is written in C and implements a number of simple mathematical operations.


## Expressions

All expressions are written in [postfix (reverse-Polish) notation][rpn], and operate on an implicit stack. All arithmetic operators (`+`, `-`, `*`, `/`, `%`) are binary operators, and reduce the stack height by 1 each time they are used. The only unary operator provided is `?`, and it does not modify the stack.

All tokens must be whitespace separated.


Valid tokens include:

    Numbers - (i.e. digits 0-9)

    +       - Add two numbers and push the result back to the stack.

    -       - Subtract two numbers and push the result back to the stack.

    *       - Multiply two numbers and push the result back to the stack.

    /       - Divide two numbers and push the result back to the stack.

    %       - Take the modulus of two numbers and push the result back to the stack.

    ?       - Print the current top-of-stack value.

Example:

    1 2 3 + + ?

Prints:

    >> 6


## Usage

To compile your own expressions, use the compiler like so:

    $ python arithc.py "your_expression_here" > bytecodefile.txt

You can then run the bytecode with:

    $ ./arith bytecodefile.txt


   [rpn]: http://en.wikipedia.org/wiki/Reverse_Polish_notation
