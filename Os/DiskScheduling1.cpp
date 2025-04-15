#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void printSchedule(const string& name, const vector<int>& order, int totalHeadMovement) {
    cout << "\n" << name << " Disk Scheduling Order:\n";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i];
        if (i != order.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Head Movement: " << totalHeadMovement << " tracks\n";
}

void fcfs(const vector<int>& requests, int head) {
    vector<int> order;
    int total = 0, current = head;

    for (int track : requests) {
        total += abs(track - current);
        current = track;
        order.push_back(track);
    }

    printSchedule("FCFS", order, total);
}

void scan(vector<int> requests, int head, int diskSize) {
    vector<int> order;
    int total = 0, current = head;

    requests.push_back(head);
    sort(requests.begin(), requests.end());

    int pos = find(requests.begin(), requests.end(), head) - requests.begin();

    // Move left
    for (int i = pos - 1; i >= 0; i--) {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    // Reach start (0)
    if (current != 0) {
        total += current;
        current = 0;
        order.push_back(0);
    }

    // Then move right from head+1
    for (int i = pos + 1; i < requests.size(); i++) {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    printSchedule("SCAN", order, total);
}

void cscan(vector<int> requests, int head, int diskSize) {
    vector<int> order;
    int total = 0, current = head;

    requests.push_back(head);
    sort(requests.begin(), requests.end());

    int pos = find(requests.begin(), requests.end(), head) - requests.begin();

    // Move right
    for (int i = pos + 1; i < requests.size(); i++) {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    // Jump from end to start
    if (current != diskSize - 1) {
        total += abs(current - (diskSize - 1));
        current = 0;
        total += diskSize - 1; // full jump from end to 0
    } else {
        current = 0;
        total += diskSize - 1;
    }
    order.push_back(0); // optional: show jump

    // Then continue from beginning to left side
    for (int i = 0; i < pos; i++) {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    printSchedule("C-SCAN", order, total);
}

int main() {
    int n, head, diskSize = 200;

    cout << "Enter Number of Tracks: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter Track Positions:\n";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter Initial Head Position: ";
    cin >> head;

    fcfs(requests, head);
    scan(requests, head, diskSize);
    cscan(requests, head, diskSize);

    return 0;
}
