LDFLAGS=-pthread
EXECS=createSemP deleteSemV waitForSig sendASig useResource mutex

all: $(EXECS)

createSemP: createSemP.o
	$(CXX) -o $@ $^ ${LDFLAGS}

createSemP.o: createSemP.cpp

deleteSemV: deleteSemV.o
	$(CXX) -o $@ $^

deleteSemV.o: deleteSemV.cpp

waitForSig: waitForSig.o
	$(CXX) -o $@ $^ ${LDFLAGS}

waitForSig.o: waitForSig.cpp

sendASig: sendASig.o
	$(CXX) -o $@ $^ ${LDFLAGS}

sendASig.o: sendASig.cpp

mutex: mutex.o
	$(CXX) -o $@ $^ ${LDFLAGS}

mutex.o: mutex.cpp

clean:
	rm -f *.o
	rm -f ${EXECS}
	rm -f *.cpp~ *.h~ *~
