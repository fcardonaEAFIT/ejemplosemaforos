#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <unistd.h>

using namespace std;


int
main(int argc, char *argv[]) {
  sem_t *ownSem;
  sem_t *agent;

  if (argc != 2) {
    cerr << "Usage: smoker <semaphore name>" << endl;
    return EXIT_FAILURE;
  }

  if ((ownSem = sem_open(argv[1], 0)) == SEM_FAILED) {
      cerr << "Semaforo fallo debido a " << errno << " " << strerror(errno) << endl;
      return EXIT_FAILURE;
  }

  if ((agent = sem_open("agente", 0)) == SEM_FAILED) {
    cerr << "Semaforo fallo debido a " << errno << " " << strerror(errno) << endl;
    return EXIT_FAILURE;
  }
 
  srandom(time(0));
  for(;;) {
    sem_wait(ownSem);
    cout << argv[1] << " smoking..." << endl;
    sleep(random() % 5);
    sem_post(agent);
  }

  return EXIT_SUCCESS;
}
