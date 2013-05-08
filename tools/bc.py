# Name: bc.py -- simplistic bytecode packer script
# Author: Philip Conrad on 4/30/2013 @ 2:35 PM
# License: MIT-License

"""
How it works:
--------------
Provide the values you wish to pack in a list of tuples, and then
call 'assemble()' on that list.
Example:
    derList = [(1, 43),(1, 43),(2, 43),(4, 43)]
    result = assemble(derList)
    print "result:'" + result + "'"

Output to a file:
------------------
Just write the assembled string out to file.

Example:
    derList = [(1, 43),(1, 43),(2, 43),(4, 43)]
    result = assemble(derList)
    outfile = open("somefile.bc", "w")
    outfile.write(result)
    outfile.flush
    outfile.close
"""

import struct, sys
from ast import literal_eval


def packNBytes(n, payload):
    """The unsigned byte pack function.

    :param n: How many bytes to use for packing the payload.
    :type n: int.
    :param payload: The integer value to pack into the bytestring.
    :type payload: int.
    :returns: str -- A packed bytestring.
    """
    final = ""
    if n == 1:
        final += struct.pack("<B", payload)
    if n == 2:
        final += struct.pack("<H", payload)
    if n == 4:
        final += struct.pack("<I", payload)
    if n == 8:
        final += struct.pack("<Q", payload)
    return final


def packNSignedBytes(n, payload):
    """The signed byte pack function.

    :param n: How many bytes to use for packing the payload.
    :type n: int.
    :param payload: The integer value to pack into the bytestring.
    :type payload: int.
    :returns: str -- A packed bytestring.
    """
    final = ""
    if n == 1:
        final += struct.pack("<b", payload)
    if n == 2:
        final += struct.pack("<h", payload)
    if n == 4:
        final += struct.pack("<i", payload)
    if n == 8:
        final += struct.pack("<q", payload)
    return final

def pack(blen, payload):
    """Creates a packed bytecode string from a (length, value) tuple.
    NOTE: This function automatically selects the signed pack
    function for signed values.

    :param blen: How many bytes to use for packing the payload.
    :type blen: int.
    :param payload: The integer value to pack into the bytestring.
    :type payload: int.
    :returns: str -- A packed bytestring.
    """
    final = ""
    if payload < 0:
        #signed case
        final += packNSignedBytes(blen, payload)
    else:
        #unsigned case
        final += packNBytes(blen, payload)
    return final


def assemble(bytelist):
    """Creates a bytecode string from a list of (length, value) tuples.

    :param bytelist: How many bytes to use for packing the payload.
    :type bytelist: (int, int) -- A Tuple.
    :returns: str -- The packed bytestring containing all of the values in 'bytelist'.
    """
    final = ""
    for pair in bytelist:
        final += pack(pair[0], pair[1])
    return final


#basic eval in main:
#example:
# $ python bc.py [(1,43),(2,43),(1,43)]
if __name__ == '__main__':
    src = sys.argv[1]
    bytelist = literal_eval(src)
    bytelist = list(bytelist)
    result = assemble(bytelist)
    print result
