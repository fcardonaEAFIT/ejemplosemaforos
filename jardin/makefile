LDFLAGS=-pthread

all: garden

garden: garden.o
	$(CXX) -o $@ $^ $(LDFLAGS)

garden.o: garden.cpp
