#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

enum SMOKER { NOTABAC, NOMATCH, NOPAPER, AGENT };

const char* name[] = { "notabaco", "nocerilla", "nopapel", "agente" };

int
main() {
  sem_t *sem[sizeof(name)/sizeof(const char*)];

  for (int i = 0; i < sizeof(name)/sizeof(const char*); i++) {
    if ((sem[i] = sem_open(name[i], // nombre
			   0)) == SEM_FAILED) {
      cerr << "Semaforo fallo debido a " << errno << " " << strerror(errno) << endl;
      return EXIT_FAILURE;
    }
  }

  srandom(time(0));
  for(;;) {
    int smoker = random() % 3; 
    sem_post(sem[smoker]);
    cout << "Wake up to: " << name[smoker] << endl;
    sem_wait(sem[AGENT]);
  }

  return EXIT_SUCCESS;
}
