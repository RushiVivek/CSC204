#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Process {
    int pid, arrival, burst, priority;
    int start = -1, finish = 0, turnaround = 0, waiting = 0;
    int remaining;
    bool completed = false;
};

// FCFS Scheduling
void fcfs(vector<Process> processes) {
    cout << "\n--- FCFS Scheduling ---\n";
    int time = 0;
    float totalTAT = 0, totalWT = 0;

    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    for (auto& p : processes) {
        if (time < p.arrival) time = p.arrival;
        p.start = time;
        p.finish = p.start + p.burst;
        p.turnaround = p.finish - p.arrival;
        p.waiting = p.turnaround - p.burst;

        time = p.finish;
        totalTAT += p.turnaround;
        totalWT += p.waiting;
    }

    cout << "PID\tAT\tBT\tST\tFT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << "Avg TAT: " << totalTAT / processes.size() << " | Avg WT: " << totalWT / processes.size() << "\n";
}

// SJF (Non-Preemptive)
void sjf(vector<Process> processes) {
    cout << "\n--- SJF (Non-Preemptive) Scheduling ---\n";
    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;
    vector<bool> done(processes.size(), false);

    while (completed < processes.size()) {
        int idx = -1;
        int minBurst = numeric_limits<int>::max();

        for (int i = 0; i < processes.size(); ++i) {
            if (!done[i] && processes[i].arrival <= time && processes[i].burst < minBurst) {
                minBurst = processes[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        processes[idx].start = time;
        processes[idx].finish = time + processes[idx].burst;
        processes[idx].turnaround = processes[idx].finish - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;

        time = processes[idx].finish;
        done[idx] = true;
        completed++;

        totalTAT += processes[idx].turnaround;
        totalWT += processes[idx].waiting;
    }

    cout << "PID\tAT\tBT\tST\tFT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << "Avg TAT: " << totalTAT / processes.size() << " | Avg WT: " << totalWT / processes.size() << "\n";
}

// Priority Scheduling (Non-Preemptive)
void priorityScheduling(vector<Process> processes) {
    cout << "\n--- Priority Scheduling (Non-Preemptive) ---\n";
    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;
    vector<bool> done(processes.size(), false);

    while (completed < processes.size()) {
        int idx = -1;
        int highestPriority = numeric_limits<int>::max();

        for (int i = 0; i < processes.size(); ++i) {
            if (!done[i] && processes[i].arrival <= time && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        processes[idx].start = time;
        processes[idx].finish = time + processes[idx].burst;
        processes[idx].turnaround = processes[idx].finish - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;

        time = processes[idx].finish;
        done[idx] = true;
        completed++;

        totalTAT += processes[idx].turnaround;
        totalWT += processes[idx].waiting;
    }

    cout << "PID\tAT\tBT\tP\tST\tFT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority << "\t"
             << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << "Avg TAT: " << totalTAT / processes.size() << " | Avg WT: " << totalWT / processes.size() << "\n";
}

// SRTF (Preemptive)
void srtf(vector<Process> processes) {
    cout << "\n--- SRTF (Preemptive SJF) Scheduling ---\n";

    int n = processes.size();
    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    for (auto& p : processes)
        p.remaining = p.burst;

    while (completed < n) {
        int idx = -1;
        int minRem = numeric_limits<int>::max();

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= time && !processes[i].completed && processes[i].remaining < minRem && processes[i].remaining > 0) {
                minRem = processes[i].remaining;
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
            processes[idx].turnaround = processes[idx].finish - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            completed++;

            totalTAT += processes[idx].turnaround;
            totalWT += processes[idx].waiting;
        }
    }

    cout << "PID\tAT\tBT\tST\tFT\tTAT\tWT\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.start << "\t" << p.finish << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << "Avg TAT: " << totalTAT / n << " | Avg WT: " << totalWT / n << "\n";
}

// MAIN
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time, Burst Time, and Priority for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrival;
        cout << "Burst Time: ";
        cin >> processes[i].burst;
        cout << "Priority (lower = higher): ";
        cin >> processes[i].priority;
    }

    fcfs(processes);
    sjf(processes);
    priorityScheduling(processes);
    srtf(processes);

    return 0;
}
