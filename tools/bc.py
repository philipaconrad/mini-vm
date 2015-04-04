# bc.py -- Simplistic bytecode packer script
# Description: Takes a list of unsigned integers (range 0-255) and
#              prints them to stdout. 
# Author:  Philip Conrad on 4/30/2013 @ 2:35 PM
# License: MIT-License

"""
How it works:
--------------
Provide the unsigned byte values you wish to pack as a list.
Example:
    byteList = [0,1,2,3, 0,0,1,2, 0,0,0,0]
    result = assemble(byteList)
    print "result:'" + result + "'"

Output to a file:
------------------
Just write the assembled string out to file.

Example:
    byteList = [0,1,2,3, 0,0,1,2, 0,0,0,0]
    result = assemble(byteList)
    outfile = open("bytecode.bc", "w")
    outfile.write(result)
    outfile.flush
    outfile.close
"""


import struct, sys
from ast import literal_eval


# example usage:
# $ python bc.py '[0,2,43,0,  3,2,0,0,  0,1,1,0,  0,0,0,0]'
if __name__ == '__main__':
    try:
        bytelist = literal_eval(sys.argv[1])
        result = [struct.pack("<B", b) for b in bytelist]
        for b in result:
            sys.stdout.write(b)
    except IndexError:
        print "USAGE: python bc.py [BYTE_VALUE_LIST]"
        print "\nExample:\n\tpython bc.py '[0,2,43,0,  3,2,0,0,  0,1,1,0,  0,0,0,0]'"
