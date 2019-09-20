#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

const char* name[] = { "notabaco", "nocerilla", "nopapel", "agente" };
int
main(void) {

  sem_t *sem[sizeof(name)/sizeof(const char*)];

  for (int i = 0; i < sizeof(name)/sizeof(const char*); i++) {
    if ((sem[i] = sem_open(name[i], // nombre
			   O_CREAT | O_EXCL, // oflags
			   S_IRUSR | S_IWUSR, // mode
			   0)) == SEM_FAILED) {
      cerr << "Semaforo fallo debido a " << errno << " " << strerror(errno) << endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
