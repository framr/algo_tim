CC=g++
LD=g++
CXXFLAGS=-Wall -std=c++11 

EXE1=apsp
objects1=apsp.o

all: $(EXE1)

$(EXE1): $(objects1)
	$(LD) -o $@ $(objects1)
#	$(LD) -pg -o $@ $(objects)


$(objects): %.o: %.cc
	$(CC) $(CXXFLAGS) $< -o $@


