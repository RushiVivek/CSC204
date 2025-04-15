#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void firstFit(vector<int> blockSize, vector<int> processSize) {
    int m = blockSize.size();
    int n = processSize.size();
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nFirst Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " of size " << processSize[i] << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void bestFit(vector<int> blockSize, vector<int> processSize) {
    int m = blockSize.size();
    int n = processSize.size();
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " of size " << processSize[i] << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void worstFit(vector<int> blockSize, vector<int> processSize) {
    int m = blockSize.size();
    int n = processSize.size();
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << " of size " << processSize[i] << " -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

int main() {
    int m, n;

    cout << "Enter number of memory blocks: ";
    cin >> m;
    vector<int> blockSize(m);
    cout << "Enter size of each memory block:\n";
    for (int i = 0; i < m; i++)
        cin >> blockSize[i];

    cout << "Enter number of processes: ";
    cin >> n;
    vector<int> processSize(n);
    cout << "Enter size of each process:\n";
    for (int i = 0; i < n; i++)
        cin >> processSize[i];

    // Use fresh copies each time since the algorithms modify them
    firstFit(blockSize, processSize);
    bestFit(blockSize, processSize);
    worstFit(blockSize, processSize);

    return 0;
}
