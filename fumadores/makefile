EXEC=crearSemaforos agente smoker destroySem
LDFLAGS=-pthread
all: $(EXEC)

crearSemaforos: crearSemaforos.o
	$(CXX) -o $@ $^ $(LDFLAGS)

agente: agente.o
	$(CXX) -o $@ $^ $(LDFLAGS)

smoker: smoker.o
	$(CXX) -o $@ $^ $(LDFLAGS)

destroySem: destroySem.o
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o
	rm -f *.*~ *~
	rm -f $(EXEC)
