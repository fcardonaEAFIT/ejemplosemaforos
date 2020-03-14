#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;
void usage(const char *program);

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

  cout << "Waiting for a signal" << endl;

  if (sem_wait(sem) == -1) {
    cerr << "Error operating over semaphore " << argv[1]
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  cout << "Signal has just arrived" << endl;
  return EXIT_SUCCESS;
}

void usage(const char *program) {
  cerr << "Usage: " << program << " <semkey>" << endl;
  _exit(EXIT_FAILURE);
}
