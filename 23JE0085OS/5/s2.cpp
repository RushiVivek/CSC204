#include <bits/stdc++.h>
using namespace std;

int n;

struct Process {
    int arrivalTime;
    int burstTime;
    int queue;
};

void FCFS(vector<Process> &processes) {
    int waitingTime[n], turnaroundTime[n];
    waitingTime[0] = 0; // First process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waitingTime[i] = processes[i - 1].burstTime + waitingTime[i - 1];
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }

    // Output the results
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << "\t" << processes[i].arrivalTime << "\t\t" 
             << processes[i].burstTime << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnaroundTime[i] << "\n";
    }
}

void SJF(vector<Process> &processes) {
    vector<int> waitingTime(n), turnaroundTime(n);
    vector<bool> completed(n, false);
    int completedCount = 0, currentTime = 0;

    while (completedCount < n) {
        int idx = -1;
        int minBurstTime = INT_MAX;

        // Find the process with the minimum burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            waitingTime[idx] = currentTime - processes[idx].arrivalTime;
            currentTime += processes[idx].burstTime;
            turnaroundTime[idx] = waitingTime[idx] + processes[idx].burstTime;
            completed[idx] = true;
            completedCount++;
        } else {
            currentTime++; // No process is ready, increment time
        }
    }

    // Output the results
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << "\t" << processes[i].arrivalTime << "\t\t" 
             << processes[i].burstTime << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnaroundTime[i] << "\n";
    }
}

void RoundRobin(vector<Process> &processes, int quantum) {
    vector<int> waitingTime(n), turnaroundTime(n);
    queue<int> q;
    int remainingBurstTime[n];
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    int currentTime = 0;
    q.push(0); // Start with the first process

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        if (remainingBurstTime[idx] > quantum) {
            currentTime += quantum;
            remainingBurstTime[idx] -= quantum;
            q.push(idx); // Re-add the process to the queue
        } else {
            currentTime += remainingBurstTime[idx];
            waitingTime[idx] = currentTime - processes[idx].arrivalTime - processes[idx].burstTime;
            remainingBurstTime[idx] = 0; // Process is completed
        }
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }

    // Output the results
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << "\t" << processes[i].arrivalTime << "\t\t" 
             << processes[i].burstTime << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnaroundTime[i] << "\n";
    }
}

int main() {
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "For P" << i << " :\n";
        cout << "Enter arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time: ";
        cin >> processes[i].burstTime;
        cout << "Enter Queue: ";
        cin >> processes[i].queue; // Complete the input for Queue
    }

    // Call scheduling algorithms here
    FCFS(processes); // Call FCFS for demonstration
    SJF(processes);  // Call SJF for demonstration
    int quantum;
    cout << "Enter quantum time for Round Robin: ";
    cin >> quantum;
    RoundRobin(processes, quantum); // Call Round Robin for demonstration

    return 0;
}
