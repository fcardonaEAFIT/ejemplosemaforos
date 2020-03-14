#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
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

  sem_t *sem;

  if ((sem = sem_open(argv[1], 0)) == SEM_FAILED) {

    cerr << "Error openning semaphore " << argv[1]
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  cout << "Adquiring a resource" << endl;

  if (sem_wait(sem) == -1) {
    cerr << "Error operating over semaphore " << argv[1]
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

  if (sem_post(sem) == -1) {
    cerr << "Error operating over semaphore " << argv[1]
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

void usage(const char *program) {
  cerr << "Usage: " << program << " <semname>" << endl;
  _exit(EXIT_FAILURE);
}
