// process_cpp.cpp
#include <iostream>
#include <unistd.h>     // for fork(), getpid(), getppid()
#include <sys/wait.h>   // for wait()
using namespace std;
int main() {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) {
        // Child process
        cout << "Child Process: PID = " << getpid()
                  << ", Parent PID = " << getppid() << endl;
        _exit(0);  // Exit the child process
    }
    else {
        // Parent process
        cout << "Parent Process: PID = " << getpid() << endl;
        wait(NULL);  // Wait for child process to terminate
        cout << "Child process terminated." << endl;
    }

    return 0;
}
