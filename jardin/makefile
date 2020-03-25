LDFLAGS=-pthread

all: garden limGarden

garden: garden.o
	$(CXX) -o $@ $^ $(LDFLAGS)

garden.o: garden.cpp

limGarden: limGarden.o
	$(CXX) -o $@ $^ $(LDFLAGS)

limGarden.o: limGarden.cpp
