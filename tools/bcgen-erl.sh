#!/bin/bash
#bytecode explanation:
#1. load 43 ('+') to R2
#2. print contents of R2
#3. load 1 into R1
#4. terminate
#                |1        |2       |3       |4
escript bc.erl "[0,2,43,0, 3,2,0,0, 0,1,1,0, 0,0,0,0]." > bytecode.txt 
