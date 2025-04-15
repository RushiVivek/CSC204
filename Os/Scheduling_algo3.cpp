#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, at, bt, ct = 0, wt = 0, tat = 0;
    bool completed = false;
};

bool arrivalCompare(Process a, Process b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter arrival time and burst time for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].pid = i + 1;
    }

    sort(p.begin(), p.end(), arrivalCompare);

    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        double max_rr = -1;

        for (int i = 0; i < n; ++i) {
            if (p[i].at <= time && !p[i].completed) {
                double rr = (double)(time - p[i].at + p[i].bt) / p[i].bt;
                if (rr > max_rr) {
                    max_rr = rr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = true;
            completed++;
        } else {
            time++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& pr : p) {
        cout << "P" << pr.pid << "\t" << pr.at << "\t" << pr.bt << "\t"
             << pr.ct << "\t" << pr.tat << "\t" << pr.wt << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int pid, at, bt, bt_rem, ct = 0, wt = 0, tat = 0, queue_no;
    bool completed = false;
};

bool arrivalCompare(Process a, Process b) {
    return a.at < b.at;
}

bool sjfCompare(Process a, Process b) {
    return a.bt < b.bt;
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum for Round Robin queue: ";
    cin >> tq;

    vector<Process> fcfsQ, sjfQ, rrQ;
    for (int i = 0; i < n; ++i) {
        Process p;
        p.pid = i + 1;
        cout << "Enter arrival time, burst time and queue number (1:FCFS, 2:SJF, 3:RR) for P" << p.pid << ": ";
        cin >> p.at >> p.bt >> p.queue_no;
        p.bt_rem = p.bt;

        if (p.queue_no == 1) fcfsQ.push_back(p);
        else if (p.queue_no == 2) sjfQ.push_back(p);
        else rrQ.push_back(p);
    }

    vector<Process> result;
    int time = 0;

    // FCFS Queue
    sort(fcfsQ.begin(), fcfsQ.end(), arrivalCompare);
    for (auto& p : fcfsQ) {
        if (time < p.at) time = p.at;
        p.ct = time + p.bt;
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;
        time = p.ct;
        result.push_back(p);
    }

    // SJF Queue
    sort(sjfQ.begin(), sjfQ.end(), arrivalCompare);
    vector<bool> done(sjfQ.size(), false);
    int completed = 0;
    while (completed < sjfQ.size()) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < sjfQ.size(); ++i) {
            if (!done[i] && sjfQ[i].at <= time && sjfQ[i].bt < min_bt) {
                min_bt = sjfQ[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            if (time < sjfQ[idx].at) time = sjfQ[idx].at;
            sjfQ[idx].ct = time + sjfQ[idx].bt;
            sjfQ[idx].tat = sjfQ[idx].ct - sjfQ[idx].at;
            sjfQ[idx].wt = sjfQ[idx].tat - sjfQ[idx].bt;
            time = sjfQ[idx].ct;
            done[idx] = true;
            result.push_back(sjfQ[idx]);
            completed++;
        } else {
            time++;
        }
    }

    // Round Robin Queue
    sort(rrQ.begin(), rrQ.end(), arrivalCompare);
    queue<int> q;
    vector<bool> inQueue(rrQ.size(), false);
    int rr_time = time;
    int rem = rrQ.size();
    int idx = 0;

    while (rem > 0 || !q.empty()) {
        while (idx < rrQ.size() && rrQ[idx].at <= rr_time) {
            q.push(idx);
            inQueue[idx] = true;
            idx++;
        }

        if (q.empty()) {
            rr_time++;
            continue;
        }

        int i = q.front(); q.pop();
        int exec_time = min(tq, rrQ[i].bt_rem);
        rr_time += exec_time;
        rrQ[i].bt_rem -= exec_time;

        // Add any newly arrived processes during this execution
        while (idx < rrQ.size() && rrQ[idx].at <= rr_time) {
            q.push(idx);
            inQueue[idx] = true;
            idx++;
        }

        if (rrQ[i].bt_rem == 0) {
            rrQ[i].ct = rr_time;
            rrQ[i].tat = rrQ[i].ct - rrQ[i].at;
            rrQ[i].wt = rrQ[i].tat - rrQ[i].bt;
            result.push_back(rrQ[i]);
            rem--;
        } else {
            q.push(i); // Push back for next round
        }
    }

    sort(result.begin(), result.end(), [](Process a, Process b) {
        return a.pid < b.pid;
    });

    cout << "\nPID\tQueue\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& p : result) {
        cout << "P" << p.pid << "\t" << p.queue_no << "\t" << p.at << "\t"
             << p.bt << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    return 0;
}
