#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, remaining, finish = 0, start = -1;
    int turnaround = 0, waiting = 0;
    bool completed = false;
};

// Round Robin (Preemptive)
void roundRobin(vector<Process> processes, int timeQuantum) {
    cout << "\n--- Round Robin Scheduling (TQ = " << timeQuantum << ") ---\n";

    int time = 0;
    queue<int> q;
    vector<bool> inQueue(processes.size(), false);
    int completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < processes.size()) {
        // Enqueue arrived processes
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrival <= time && processes[i].remaining > 0 && !inQueue[i]) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front(); q.pop();
        inQueue[idx] = false;

        if (processes[idx].start == -1)
            processes[idx].start = time;

        int execTime = min(timeQuantum, processes[idx].remaining);
        processes[idx].remaining -= execTime;
        time += execTime;

        
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrival > time - execTime && processes[i].arrival <= time && processes[i].remaining > 0 && !inQueue[i])
                q.push(i), inQueue[i] = true;
        }

        if (processes[idx].remaining > 0) {
            q.push(idx);
            inQueue[idx] = true;
        } else {
            processes[idx].completed = true;
            processes[idx].finish = time;
            processes[idx].turnaround = processes[idx].finish - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            completed++;

            totalTAT += processes[idx].turnaround;
            totalWT += processes[idx].waiting;
        }
    }

    cout << "PID\tAT\tBT\tST\tFT\tTAT\tWT\n";
    for (const auto& p : processes)
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";

    cout << "Average TAT: " << totalTAT / processes.size() << " | Average WT: " << totalWT / processes.size() << endl;
}

// LJF (Longest Job First — Preemptive)
void ljf(vector<Process> processes) {
    cout << "\n--- LJF (Preemptive) Scheduling ---\n";

    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    for (auto &p : processes) p.remaining = p.burst;

    while (completed < processes.size()) {
        int idx = -1;
        int maxBurst = -1;

        for (int i = 0; i < processes.size(); ++i) {
            if (!processes[i].completed && processes[i].arrival <= time && processes[i].burst > maxBurst && processes[i].remaining > 0) {
                maxBurst = processes[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (processes[idx].start == -1)
            processes[idx].start = time;

        processes[idx].remaining--;
        time++;

        if (processes[idx].remaining == 0) {
            processes[idx].completed = true;
            processes[idx].finish = time;
            processes[idx].turnaround = time - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            completed++;

            totalTAT += processes[idx].turnaround;
            totalWT += processes[idx].waiting;
        }
    }

    cout << "PID\tAT\tBT\tST\tFT\tTAT\tWT\n";
    for (const auto &p : processes)
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";

    cout << "Average TAT: " << totalTAT / processes.size() << " | Average WT: " << totalWT / processes.size() << endl;
}

// LRTF (Longest Remaining Time First — Preemptive)
void lrtf(vector<Process> processes) {
    cout << "\n--- LRTF (Preemptive) Scheduling ---\n";

    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    for (auto &p : processes) p.remaining = p.burst;

    while (completed < processes.size()) {
        int idx = -1;
        int maxRemaining = -1;

        for (int i = 0; i < processes.size(); ++i) {
            if (!processes[i].completed && processes[i].arrival <= time && processes[i].remaining > maxRemaining) {
                maxRemaining = processes[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (processes[idx].start == -1)
            processes[idx].start = time;

        processes[idx].remaining--;
        time++;

        if (processes[idx].remaining == 0) {
            processes[idx].completed = true;
            processes[idx].finish = time;
            processes[idx].turnaround = time - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            completed++;

            totalTAT += processes[idx].turnaround;
            totalWT += processes[idx].waiting;
        }
    }

    cout << "PID\tAT\tBT\tST\tFT\tTAT\tWT\n";
    for (const auto &p : processes)
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";

    cout << "Average TAT: " << totalTAT / processes.size() << " | Average WT: " << totalWT / processes.size() << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << ":\n";
        cout << "Arrival Time: "; cin >> processes[i].arrival;
        cout << "Burst Time: "; cin >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }

    vector<Process> rrInput = processes;
    roundRobin(rrInput, 2);

    vector<Process> ljfInput = processes;
    ljf(ljfInput);

    vector<Process> lrtfInput = processes;
    lrtf(lrtfInput);

    return 0;
}
