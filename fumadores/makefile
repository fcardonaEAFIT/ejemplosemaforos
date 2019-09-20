all: crearSemaforos agente smoker

crearSemaforos: crearSemaforos.o
	$(CXX) -o $@ $^ -pthread

agente: agente.o
	$(CXX) -o $@ $^ -pthread

smoker: smoker.o
	$(CXX) -o $@ $^ -pthread
