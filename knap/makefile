CC=g++
LD=g++
#CFLAGS=-Wall -pg
CXXFLAGS=-Wall

EXE1 = knapsack
EXE2 = knapsack_dfs
objects1 = knapsack.o
objects2 = knapsack_dfs.o

all: $(EXE1) $(EXE2)

$(EXE1): $(objects1)
	$(LD) -o $@ $(objects1)
#	$(LD) -pg -o $@ $(objects)

$(EXE2): $(objects2)
	$(LD) -o $@ $(objects2)
#	$(LD) -pg -o $@ $(objects)


$(objects): %.o: %.cc
	$(CC) -c $(CXXFLAGS) $< -o $@


