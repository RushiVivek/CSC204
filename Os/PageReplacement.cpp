#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

void printFrames(const vector<int>& frames) {
    cout << "[ ";
    for (int page : frames)
        cout << page << " ";
    cout << "]\n";
}

int simulateFIFO(vector<int> pages, int frameCount) {
    queue<int> q;
    unordered_set<int> inMemory;
    int pageFaults = 0;

    cout << "\nFIFO Page Replacement:\n";
    for (int page : pages) {
        if (inMemory.find(page) == inMemory.end()) {
            // Page Fault
            pageFaults++;
            if ((int)q.size() == frameCount) {
                int removed = q.front();
                q.pop();
                inMemory.erase(removed);
            }
            q.push(page);
            inMemory.insert(page);
            cout << "Page " << page << " -> Page Fault\t";
        } else {
            cout << "Page " << page << " -> Hit\t\t";
        }

        // Print current state of memory
        vector<int> mem;
        queue<int> temp = q;
        while (!temp.empty()) {
            mem.push_back(temp.front());
            temp.pop();
        }
        printFrames(mem);
    }

    cout << "Total Page Faults (FIFO): " << pageFaults << "\n";
    return pageFaults;
}

int simulateOptimal(vector<int> pages, int frameCount) {
    vector<int> frames;
    int pageFaults = 0;

    cout << "\nOptimal Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        auto it = find(frames.begin(), frames.end(), page);
        if (it == frames.end()) {
            // Page Fault
            pageFaults++;
            if ((int)frames.size() < frameCount) {
                frames.push_back(page);
            } else {
                // Find the page not used for the longest time in future
                int farthest = -1, index = -1;
                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == frames[j])
                            break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        index = j;
                    }
                }
                frames[index] = page;
            }
            cout << "Page " << page << " -> Page Fault\t";
        } else {
            cout << "Page " << page << " -> Hit\t\t";
        }
        printFrames(frames);
    }

    cout << "Total Page Faults (Optimal): " << pageFaults << "\n";
    return pageFaults;
}

int simulateLRU(vector<int> pages, int frameCount) {
    vector<int> frames;
    unordered_map<int, int> lastUsed;
    int pageFaults = 0;

    cout << "\nLRU Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        auto it = find(frames.begin(), frames.end(), page);
        if (it == frames.end()) {
            // Page Fault
            pageFaults++;
            if ((int)frames.size() < frameCount) {
                frames.push_back(page);
            } else {
                // Find least recently used
                int lruIndex = 0;
                int minUsed = i;
                for (int j = 0; j < frames.size(); j++) {
                    if (lastUsed[frames[j]] < minUsed) {
                        minUsed = lastUsed[frames[j]];
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = page;
            }
            cout << "Page " << page << " -> Page Fault\t";
        } else {
            cout << "Page " << page << " -> Hit\t\t";
        }

        lastUsed[page] = i;
        printFrames(frames);
    }

    cout << "Total Page Faults (LRU): " << pageFaults << "\n";
    return pageFaults;
}

int main() {
    int frameCount, n;

    cout << "Enter number of frames: ";
    cin >> frameCount;

    cout << "Enter number of pages in reference string: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    simulateFIFO(pages, frameCount);
    simulateOptimal(pages, frameCount);
    simulateLRU(pages, frameCount);

    return 0;
}