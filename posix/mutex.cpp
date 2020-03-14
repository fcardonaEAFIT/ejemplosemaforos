#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

const int BUFFER_SIZE = 8192;

void fillBuffer(char *buffer, const char c, const int size);
void processingChild(char c, sem_t *mutex);

int
main(int argc, const char *argv[]) {

  sem_t mutex;

  if (sem_init(&mutex, 1, 1) == -1) {

    cerr << "Error openning unnamed semaphore "
	 << " error: " << errno << " "
	 << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  pid_t child1;
  pid_t child2;

  if ((child1 = fork()) == 0) { // First child
    processingChild('a', &mutex);
  }
  else {

    if ((child2 = fork()) == 0) { // Second child
      processingChild('X', &mutex);
    }
  }

  int status;

  waitpid(child1, &status, 0);
  waitpid(child2, &status, 0);

  return EXIT_SUCCESS;
}

void usage(const char *program) {
  cerr << "Usage: " << program << " <semkey>" << endl;
  _exit(EXIT_FAILURE);
}


void fillBuffer(char *buffer, const char c, const int size) {

  for (int i = 0; i < size - 2; i++) buffer[i] = c;

  buffer[size-2] = '\n';
  buffer[size-1] = '\0';
}

void processingChild(const char c, sem_t *mutex) {
  char *buffer = new char[BUFFER_SIZE];

  fillBuffer(buffer, c, BUFFER_SIZE);

  for (;;) {

    if (sem_wait(mutex) == -1) {
      cerr << "Error operating over unamed semaphore: "
	   << errno << " "
	   << strerror(errno) << endl;
      _exit(EXIT_FAILURE);
    }

    cout << buffer;

    if (sem_post(mutex) == -1) {
      cerr << "Error operating over unamed semaphore: "
	   << " error: " << errno << " "
	   << strerror(errno) << endl;
	_exit(EXIT_FAILURE);
    }
  }
}
