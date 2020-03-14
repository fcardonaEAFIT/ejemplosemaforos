#include <semaphore.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <iostream>

using namespace std;
void usage(const char *program);

int
main(int argc, const char *argv[]) {

  if (argc != 2)
    usage(argv[0]);

  if (sem_unlink(argv[1]) == -1) {

    cerr << "Error opeing semaphore " << argv[1]
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
