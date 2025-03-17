#include <bits/stdc++.h>
using namespace std;

struct process {
    int name;
    int at, bt, ct, wt, tt;
    int completed;
    float ntt;

    process() {
        name = at = bt = ct = wt = tt = completed = ntt = 0;
    }

    process(int n, int a, int b) {
        name = n;
        at = a;
        bt = b;
        ct = wt = tt = completed = ntt = 0;
    }
};

vector<process*> p;

int n;

bool cmp(process* a, process* b) {
    return a->at < b->at;
}

int main() {
    int i, j, sum_bt = 0;
    float t, avgwt = 0, avgtt = 0;
    cout << "Enter number of process: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter the Arrival and Burst times for process " << i << " : ";
        int at, bt;
        cin >> at >> bt;
        sum_bt += bt;
        process* temp = new process(i + 1, at, bt);
        p.push_back(temp);
    }
    // 5
    // 0 3
    // 2 6
    // 4 4
    // 6 5
    // 8 2

    sort(p.begin(), p.end(), cmp);

    for (t = p[0]->at; t < sum_bt;) {
        float hrr = -9999;
        float temp;
        int loc;
        for (i = 0; i < n; i++) {
            if (p[i]->at <= t && p[i]->completed != 1) {
                temp = (p[i]->bt + (t - p[i]->at)) / p[i]->bt;

                if (hrr < temp) {
                    hrr = temp;
                    loc = i;
                }
            }
        }

        t += p[loc]->bt;
        p[loc]->wt = t - p[loc]->at - p[loc]->bt;
        p[loc]->tt = t - p[loc]->at;
        avgtt += p[loc]->tt;
        p[loc]->ntt = ((float)p[loc]->tt / p[loc]->bt);
        p[loc]->completed = 1;
        avgwt += p[loc]->wt;
    }
    cout << "\nAverage waiting time: " << avgwt / n << endl;
    cout << "Average Turn Around time:" << avgtt / n;
}
