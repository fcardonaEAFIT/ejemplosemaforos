#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include "semun.h"
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

  string ssemkey { argv[1] };

  key_t key = stoi(ssemkey);

  int sem;

  if ((sem = semget(key, 1,
		    IPC_CREAT | IPC_EXCL
		    | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP )) == -1) {

    cerr << "Error creating semaphore " << ssemkey
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  union semun arg;

  arg.val = 0;

  if (argc != 3) {
    string val = argv[2];
    arg.val = stoi(val);
  }

  if (semctl(sem, 0, SETVAL, arg) == -1) {
    cerr << "Error setting value for semaphore " << sem
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
