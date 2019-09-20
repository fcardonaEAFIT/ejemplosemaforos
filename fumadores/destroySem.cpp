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

  for (int i = 0; i < sizeof(name)/sizeof(const char*); i++) {
    if (sem_unlink(name[i]) == -1) {
      cerr << "Destroy semaphore failed because " << errno << " " << strerror(errno) << endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
