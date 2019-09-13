#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const int N = 10;
sem_t vacio, lleno, mutex;
int buffer[N];
int entra, sale, cantidad;

void* consumidor(void *);
void* productor(void *);

int
main() {

  entra = sale = cantidad = 0;

  sem_init(&vacio, 0, N);
  sem_init(&lleno, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_t hprod, hcon;
  pthread_create(&hcon, nullptr, consumidor, nullptr);
  pthread_create(&hprod, nullptr, productor, nullptr);

  void *status;

  pthread_join(hcon, &status);
  pthread_join(hprod, &status);

  return 0;
}

void*
productor(void *) {

  int var = 0;
  
  for (;;) {
    sem_wait(&vacio);
    sem_wait(&mutex);
    buffer[entra] = var++;
    entra = (entra + 1) % N;
    cantidad++;
    sem_post(&mutex);
    sem_post(&lleno);
    sleep(1);
  }
}


void*
consumidor(void *) {

  int valor;

  for (;;) {
    sem_wait(&lleno);
    sem_wait(&mutex);
    valor = buffer[sale];
    sale = (sale + 1) % N;
    cantidad--;
    sem_post(&mutex);
    sem_post(&vacio);
    cout << valor << endl;
  }
}
