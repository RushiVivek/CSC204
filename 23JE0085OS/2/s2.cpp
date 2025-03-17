#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void pri(int id) {
    cout << "Thread: " << id << " is started.\n";

    this_thread::sleep_for(chrono::seconds(2));

    cout << "Thread: " << id << " is running.\n";

    this_thread::sleep_for(chrono::seconds(2));

    cout << "Thread: " << id << " is finished.\n";
}

int main() {
    cout << "Main thread started.\n";

    thread t1(pri, 1);
    thread t2(pri, 2);

    t1.join();
    t2.join();

    cout << "Main thread finished.\n";

    return 0;
}
