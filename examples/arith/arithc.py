# arith.py -- Simple (RPN) Arithmetic Expression Compiler.
# Description: Parses simple arithmetic expressions in RPN form and 
#              generates bytecode to run them on the VM.
# Author:  Philip Conrad on 2015-04-04 @ 9:58 PM
# License: MIT-License


import struct, sys
from ast import literal_eval


errno = 0


def parse(expr):
    out = []
    tokens = expr.split()
    for token in tokens:
        if token == ' ':
            pass
        elif token.isdigit():
            out.append( int(token) )
        elif token in ['+', '-', '*', '/', '%', '?']:
            out.append(token)
        else:
            print "Warning: Unrecognized token: " + str(token) + "\n"
    return out


def assemble(parse_stack):
    out = []
    num_regs = 16
    stack_top = 0
    i = 0
    global errno
    for item in parse_stack:
        if isinstance(item, int):
            out += [ord('$'), stack_top, item, 0]
            stack_top += 1
            i += 1
        elif item in ['+', '-', '*', '/', '%']:
            stack_top -= 1
            out += [ord(item), stack_top-1, stack_top, stack_top-1]
            i += 1
        elif item == '?':
            out += [ord('?'), stack_top-1, 0, 0]
            i += 1
        else:
            print "Warning: Unknown opcode. Output may be incorrect."
            i += 1
        if stack_top >= 17:
            print "Error: In term " + str(i) + ": Too many values pushed onto stack. Limit is: " + str(num_regs)
            del out[-4:]
            errno = 1
            break
        if stack_top <= 0:
            print "Error: In term " + str(i) + ": Too many operators. Stack will underflow."
            del out[-4:]
            errno = 1
            break

    out += [ord('#'), 0, 0, 0]
    return out


# Example usage:
# $ python arithc.py '1 2 3 + + ?'
if __name__ == '__main__':
    try:
        bytelist = assemble(parse(sys.argv[1]))
        result = [struct.pack("<B", b) for b in bytelist]
        if errno == 0:
            for b in result:
                sys.stdout.write(b)
    except IndexError:
        print "USAGE: python arithc.py [POSTFIX_EXPR]"
        print "\nExample:\n\tpython arithc.py '1 2 3 + + ?'"
