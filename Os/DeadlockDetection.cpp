#include <iostream>
using namespace std;

#define P 5  // Number of processes
#define R 3  // Number of resources

int main() {
    int allocation[P][R] = {
        {0, 1, 0}, 
        {2, 0, 0}, 
        {3, 0, 2}, 
        {2, 1, 1}, 
        {0, 0, 2}
    };

    int request[P][R] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
    };

    int available[R] = {1, 0, 0};
    bool finish[P] = {false};

    int work[R];
    for (int i = 0; i < R; i++) work[i] = available[i];

    bool deadlock = false;
    while (true) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < R; j++) {
                    if (request[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) break;
    }

    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            cout << "Deadlock detected! Process " << i << " is in deadlock.\n";
            deadlock = true;
        }
    }

    if (!deadlock) cout << "No deadlock detected.\n";

    return 0;
}
