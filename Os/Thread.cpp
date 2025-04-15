// thread_cpp.cpp
#include <iostream>
#include <thread>
using namespace std;
void threadFunction() {
    cout << "Thread running. Thread ID: " << this_thread::get_id() << endl;
}

int main() {
    thread t(threadFunction);  // Create thread

    // Wait for thread to finish
    t.join();

    cout << "Thread has terminated." << endl;

    return 0;
}
