all: crearSemaforos agente smoker destroySem

crearSemaforos: crearSemaforos.o
	$(CXX) -o $@ $^ -pthread

agente: agente.o
	$(CXX) -o $@ $^ -pthread

smoker: smoker.o
	$(CXX) -o $@ $^ -pthread

destroySem: destroySem.o
	$(CXX) -o $@ $^ -pthread
