mini-vm
=======

A small, register-based virtual machine (bytecode interpreter) in C.


### How it works

Each bytecode instruction is 4 bytes long.

      0   1   2   3
    +---+---+---+---+
    | A | B | C | D |
    +---+---+---+---+

    A - Instruction ID. This is the index of the function in the function table you wish to call.
    B - Register #1. (usually the destination register)
    C - Register #2. (usually an argument source register)
    D - Register #3. (usually an argument source register)

Instead of the usual switch/case-based architecture most bytecode interpreters 
use, I chose to go with a table of function pointers whose indices correspond 
with particular instruction IDs.

An interpreter can be initialized by calling `initVMContext()` and supplying 
the appropriate parameters.

The interpreter's state has to be advanced one instruction at a time by 
by calling `stepVMContext()` repeatedly. In the example programs, this is 
typically done with a simple `while` loop.

Termination is not accounted for by default. Adding a custom **halt** 
instruction or some sort of status register are both plausible solutions.


### Build

 - On *nix platforms, just type `make` to build mini-vm as a static library. To build the examples, just type `make test` in each example's directory.
 - For Windows: An MSVC 2010 Project file is provided under `/msvc`. Double click on it to generate a solution file.


### Documentation

 - Look under the `/examples` folder to see examples of mini-vm in action.
 - Also worth reading: [the project's site][1]. The bytecode format and the structure of the VM are explained here.


### MIT License

Copyright (c) 2013 Philip Conrad.
All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


   [1]: http://philipaconrad.github.io/mini-vm/
