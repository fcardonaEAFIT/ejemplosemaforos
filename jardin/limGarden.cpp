#include <iostream>
#include <cstdlib>
#include <time.h>
#include <pthread.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

const int MMIN = 1;
const int MMAX = 10;

void* person(void *);
void* admin(void *);
void usage(const char *progname);
void waiting();

class Garden {
public:
  Garden(int max);
  int getPersons();
  void enter();
  void leave();
private:
  int npersons;
  sem_t mutex;
  sem_t sMax;
};

int
main(int argc, char *argv[]) {

  if (argc != 3)
    usage(argv[0]);

  string sPersons = argv[1];
  int nPersons = stoi(sPersons);
  string sMax = argv[2];
  int nMax = stoi(sMax);

  Garden garden(nMax);
  

  pthread_t person_threads[nPersons];
  pthread_t admin_thread;

  pthread_create(&admin_thread, NULL,
		admin, (void *) &garden);

  for (int i = 0; i < nPersons; i++) {

    pthread_create(&person_threads[i], NULL,
		   person, (void *) &garden);
  }

  void *status;
  pthread_join(admin_thread, &status);

  srandom(time(nullptr));
}

void*
person(void *arg) {
  Garden* garden = (Garden*) arg;

  for (;;) {
    cout << "Leaving a live" << endl;
    waiting();
    cout << "Entering" << endl;
    garden->enter();
    waiting();
    cout << "Leaving" << endl;
    garden->leave();
  }
}

void*
admin(void *arg) {
  Garden* garden = (Garden*) arg;

  for(;;) {
    waiting();
    cout << garden->getPersons() << endl;
  }
}

void
waiting() {
  sleep((int) (random() % (MMAX - MMIN) + MMIN));
}

void
usage(const char *program) {
  cerr << "Usage: " << program << " nPersons maxPersonas" << endl;
  _exit(EXIT_FAILURE);
}


Garden::Garden(int max) : npersons(0) {
  sem_init(&mutex, 0, 1);
  sem_init(&sMax, 0, max);
}

int
Garden::getPersons() {
  sem_wait(&mutex);
  int temp = npersons;
  sem_post(&mutex);
  return npersons;
}

void
Garden::enter() {
  sem_wait(&sMax);
  sem_wait(&mutex);
  npersons++;
  sem_post(&mutex);
}

void
Garden::leave() {
  sem_wait(&mutex);
  npersons--;
  sem_post(&mutex);
  sem_post(&sMax);
}
