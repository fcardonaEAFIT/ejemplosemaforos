EXECS=createSemV deleteSemV waitForSig sendASig useResource mutex

all: $(EXECS)

createSemV: createSemV.o
	$(CXX) -o $@ $^

createSemV.o: createSemV.cpp semun.h

deleteSemV: deleteSemV.o
	$(CXX) -o $@ $^

deleteSemV.o: deleteSemV.cpp

waitForSig: waitForSig.o
	$(CXX) -o $@ $^

waitForSig.o: waitForSig.cpp

sendASig: sendASig.o
	$(CXX) -o $@ $^

sendASig.o: sendASig.cpp

mutex: mutex.o
	$(CXX) -o $@ $^

mutex.o: mutex.cpp

clean:
	rm -f *.o
	rm -f ${EXECS}
	rm -f *.cpp~ *.h~ *~
