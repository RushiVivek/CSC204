#include <bits/stdc++.h>
using namespace std;

class DeadlockDetector {
   private:
    int p, r;

    vector<vector<int>> alloc, req;
    vector<int> avail;
    vector<bool> finish;

   public:
    DeadlockDetector(int processes, int resources) : p(processes), r(resources) {
        alloc.resize(p, vector<int>(r));
        req.resize(p, vector<int>(r));
        avail.resize(r);
        finish.resize(p);
    }

    void setAlloc(const vector<vector<int>>& allocation) {
        alloc = allocation;
    }

    void setReq(const vector<vector<int>>& request) {
        req = request;
    }

    void setAvail(const vector<int>& available) {
        avail = available;
    }

    bool detect() {
        vector<int> work = avail;
        vector<bool> fini(p, 0);

        while (true) {
            bool found = false;

            for (int i = 0; i < p; ++i) {
                if (!fini[i]) {
                    bool canAlloc = 1;
                    for (int j = 0; j < r; ++j) {
                        if (req[i][j] > work[j]) {
                            canAlloc = 0;
                            break;
                        }
                    }
                    if (canAlloc) {
                        for (int j = 0; j < r; ++j) {
                            work[j] += alloc[i][j];
                        }
                        fini[i] = 1;
                        found = 1;
                    }
                }
            }
            if (!found) break;
        }

        finish = fini;

        for (auto f : fini) {
            if (!f) return 1;
        }
        return 0;
    }

    void print() {
        cout << "Deadlocked processes: ";
        for (int i = 0; i < p; ++i) {
            if (!finish[i]) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
};

int main() {
    int p = 5, r = 3;
    DeadlockDetector deadlock(p, r);

    vector<vector<int>> alloc = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    deadlock.setAlloc(alloc);

    vector<vector<int>> req = {{2, 0, 2}, {1, 0, 2}, {0, 0, 0}, {1, 0, 0}, {0, 2, 0}};
    deadlock.setReq(req);

    vector<int> avail = {0, 0, 0};
    deadlock.setAvail(avail);

    if (deadlock.detect()) {
        cout << "Deadlock detected.\n";
        deadlock.print();
    } else {
        cout << "No deadlock detected.\n";
    }
    return 0;
}