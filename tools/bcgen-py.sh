#bytecode explanation:
#1. load 43 ('+') to R2
#2. print contents of R2
#3. load 1 into R1
#4. terminate
#              |1                        |2                       |3                       |4
python bc.py '[(1,0),(1,2),(1,43),(1,0), (1,3),(1,2),(1,0),(1,0), (1,0),(1,1),(1,1),(1,0), (4,0)]' > bytecode.txt
