EXEC=prodcons
LDFLAGS=-pthread

all: $(EXEC)

prodcons: prodcons.o
	$(CXX) -o $@ $^ $(LDFLAGS)

prodcons.o: prodcons.cpp

clean:
	rm -f *~ *.*~ *.o
	rm -f $(EXEC)
