import numpy as np

def processLine(line):
    split = line.rstrip().split(",")
    i = strats.index(split[0])
    j = strats.index(split[3])

    winPerTable[i][j] = float(split[1])
    winPerTable[j][i] = float(split[4])

    ptDiffTable[i][j] = float(split[2])
    ptDiffTable[j][i] = float(split[5])

# SCRIPT -----------------------------------------------------------------------------------

strats = []
numGames = -1
winPerTable = np.zeros(1)
ptDiffTable = np.zeros(1)

fileName = "C:/Users/natha/Documents/cribbage/Cribbage/Analysis/out/allH-HeuristicP.out"

fin = open(fileName, 'r')

line = fin.readline()
strats = line.rstrip().split(',')

line = fin.readline()
numGames = int(line.rstrip().split(',')[1])

shape = (len(strats), len(strats))
winPerTable = np.zeros(shape)
ptDiffTable = np.zeros(shape)

line = fin.readline()

for line in fin:
    processLine(line)

fin.close()

print("strategies:", strats)
print("numGames:", numGames)
print("---------- win percentage table ----------")
print(winPerTable)
print("----------- avg pt diff table ------------")
print(ptDiffTable)
