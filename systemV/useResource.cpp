#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "semun.h"
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;
void usage(const char *program);

const int MMIN = 1;
const int MMAX = 10;

int
main(int argc, const char *argv[]) {

  if (argc != 2)
    usage(argv[0]);

  string ssemkey { argv[1] };

  key_t key = stoi(ssemkey);

  int sem;

  if ((sem = semget(key, 1, 0)) == -1) {

    cerr << "Error openning semaphore " << ssemkey
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  cout << "Adquiring a resource" << endl;

  struct sembuf semCtrl;

  semCtrl.sem_num = 0;
  semCtrl.sem_op  = -1;
  semCtrl.sem_flg = 0;

  if (semop(sem, &semCtrl, 1) == -1) {
    cerr << "Error operating over semaphore " << ssemkey
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  srandom(time(nullptr));

  int nTimes = (int) (random() % (MMAX - MMIN) + MMIN);

  for (int i = 0; i < nTimes; i++) {
    cout << "Using resource adquired" << endl;
    sleep((int) (random() % (MMAX - MMIN) + MMIN));
  }

  cout << "Freeing resource" << endl;

  semCtrl.sem_num = 0;
  semCtrl.sem_op  = 1;
  semCtrl.sem_flg = 0;

  if (semop(sem, &semCtrl, 1) == -1) {
    cerr << "Error operating over semaphore " << ssemkey
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

void usage(const char *program) {
  cerr << "Usage: " << program << " <semkey>" << endl;
  _exit(EXIT_FAILURE);
}
