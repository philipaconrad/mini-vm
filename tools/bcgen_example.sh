#bytecode explanation:
#              | load 43 ('+') to R2     | print contents of R2   | load 1 into R1
python bc.py '[(1,0),(1,2),(1,43),(1,0), (1,3),(1,2),(1,0),(1,0), (1,0),(1,1),(1,1),(1,0), (4,0)]' > bytecode.txt
