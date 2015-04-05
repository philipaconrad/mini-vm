Original Example
----------------

This demo was shipped with most of the early versions of mini-vm, and is retained for legacy purposes. It only includes enough functionality to print out a character from the value of a register.


## Usage

One can assemble custom bytecode by feeding a list of integers (range 0-255) to the `bc.py` script and redirecting the output to a file.

    $ python bc.py "[0,2,65,0,  3,2,0,0,  0,1,1,0,  0,0,0,0]" > bytecode.txt

In the above snippet, the ASCII value for 'A' (65, in decimal) is loaded into register 2. See the `example.c` file to see what's possible.


## Warning

Again, please remember that this is old code, and will probably be removed/replaced in the future.
