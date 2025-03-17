#include <iostream>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "fork failure: " << strerror(errno) << "\n";
	exit(EXIT_FAILURE);
    } else if (pid == 0) {
	cout << "Child process with pid=" << getpid() << " started\n";
    } else {
	cout << "Parent process with pid=" << getpid() << " created a child with pid=" << pid << "\n";
	int status;
	waitpid(pid, &status, 0);
	cout << "Child process ended.\n";
    }
    
    return 0;
}
