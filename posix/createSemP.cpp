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

  if (argc == 1)
    usage(argv[0]);

  sem_t *sem;

  int value = 0;

  if (argc == 3) {
    string val = argv[2];
    value = stoi(val);
  }

  if ((sem = sem_open(argv[1],
		      O_CREAT | O_EXCL,
		      S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
		      value)) == SEM_FAILED) {

    cerr << "Error creating semaphore " << argv[1]
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  sem_close(sem);

  return EXIT_SUCCESS;
}

void usage(const char *program) {
  cerr << "Usage: " << program << " <semkey>" << endl;
  _exit(EXIT_FAILURE);
}
