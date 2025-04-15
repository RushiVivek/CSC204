#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

void printSchedule(const string &name, const vector<int> &order, int totalHeadMovement)
{
    cout << "\n"
         << name << " Disk Scheduling Order:\n";
    for (size_t i = 0; i < order.size(); i++)
    {
        cout << order[i];
        if (i != order.size() - 1)
            cout << " -> ";
    }
    cout << "\nTotal Head Movement: " << totalHeadMovement << " tracks\n";
}

void look(vector<int> requests, int head)
{
    vector<int> order;
    int total = 0, current = head;

    sort(requests.begin(), requests.end());
    auto it = find(requests.begin(), requests.end(), head);
    int pos = (it != requests.end()) ? distance(requests.begin(), it) : lower_bound(requests.begin(), requests.end(), head) - requests.begin();

    // Move right
    for (int i = pos; i < requests.size(); i++)
    {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    // Then left
    for (int i = pos - 1; i >= 0; i--)
    {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    printSchedule("LOOK", order, total);
}

void clook(vector<int> requests, int head)
{
    vector<int> order;
    int total = 0, current = head;

    sort(requests.begin(), requests.end());
    auto it = find(requests.begin(), requests.end(), head);
    int pos = (it != requests.end()) ? distance(requests.begin(), it) : lower_bound(requests.begin(), requests.end(), head) - requests.begin();

    // Move right
    for (int i = pos; i < requests.size(); i++)
    {
        total += abs(current - requests[i]);
        current = requests[i];
        order.push_back(current);
    }

    // Jump to the lowest request
    if (pos > 0)
    {
        total += abs(current - requests[0]);
        current = requests[0];
        order.push_back(current);

        for (int i = 1; i < pos; i++)
        {
            total += abs(current - requests[i]);
            current = requests[i];
            order.push_back(current);
        }
    }

    printSchedule("C-LOOK", order, total);
}

void sstf(vector<int> requests, int head)
{
    vector<int> order;
    int total = 0, current = head;
    vector<bool> visited(requests.size(), false);

    for (int i = 0; i < requests.size(); i++)
    {
        int shortest = INT_MAX, index = -1;
        for (int j = 0; j < requests.size(); j++)
        {
            if (!visited[j] && abs(current - requests[j]) < shortest)
            {
                shortest = abs(current - requests[j]);
                index = j;
            }
        }

        if (index != -1)
        {
            total += abs(current - requests[index]);
            current = requests[index];
            visited[index] = true;
            order.push_back(current);
        }
    }

    printSchedule("SSTF", order, total);
}

int main()
{
    int n;
    cout << "Enter Number of Tracks: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter Track Positions:\n";
    for (int i = 0; i < n; i++)
        cin >> requests[i];

    int head = requests[0];           // First is the head
    requests.erase(requests.begin()); // Remove head from request list

    look(requests, head);
    clook(requests, head);
    sstf(requests, head);

    return 0;
}
