#include <bits/stdc++.h>
using namespace std;

struct MemoryBlock {
    int size;
    bool isAllocated;
};

class MemoryAllocator {
private:
    vector<MemoryBlock> blocks;

public:
    MemoryAllocator(vector<int> sizes) {
        for (int size : sizes) {
            blocks.push_back({size, false});
        }
    }

    void bestFit(int requestSize) {
        int bestIndex = -1;
        for (int i = 0; i < blocks.size(); i++) {
            if (!blocks[i].isAllocated && blocks[i].size >= requestSize) {
                if (bestIndex == -1 || blocks[i].size < blocks[bestIndex].size) {
                    bestIndex = i;
                }
            }
        }
        if (bestIndex != -1) {
            blocks[bestIndex].isAllocated = true;
            cout << "Best Fit: Allocated " << requestSize << " in block of size " << blocks[bestIndex].size << endl;
        } else {
            cout << "Best Fit: No suitable block found for " << requestSize << endl;
        }
    }

    void worstFit(int requestSize) {
        int worstIndex = -1;
        for (int i = 0; i < blocks.size(); i++) {
            if (!blocks[i].isAllocated && blocks[i].size >= requestSize) {
                if (worstIndex == -1 || blocks[i].size > blocks[worstIndex].size) {
                    worstIndex = i;
                }
            }
        }
        if (worstIndex != -1) {
            blocks[worstIndex].isAllocated = true;
            cout << "Worst Fit: Allocated " << requestSize << " in block of size " << blocks[worstIndex].size << endl;
        } else {
            cout << "Worst Fit: No suitable block found for " << requestSize << endl;
        }
    }

    void nextFit(int requestSize) {
        static int lastAllocatedIndex = 0;
        for (int i = 0; i < blocks.size(); i++) {
            int index = (lastAllocatedIndex + i) % blocks.size();
            if (!blocks[index].isAllocated && blocks[index].size >= requestSize) {
                blocks[index].isAllocated = true;
                lastAllocatedIndex = index;
                cout << "Next Fit: Allocated " << requestSize << " in block of size " << blocks[index].size << endl;
                return;
            }
        }
        cout << "Next Fit: No suitable block found for " << requestSize << endl;
    }

    void printMemory() {
        cout << "Memory Blocks:" << endl;
        for (int i = 0; i < blocks.size(); i++) {
            cout << "Block " << i << ": Size = " << blocks[i].size << ", "
                 << (blocks[i].isAllocated ? "Allocated" : "Free") << endl;
        }
    }
};

int main() {
    vector<int> sizes = {100, 500, 200, 300, 600};
    MemoryAllocator allocator(sizes);

    allocator.printMemory();
    allocator.bestFit(212);
    allocator.printMemory();
    allocator.worstFit(417);
    allocator.printMemory();
    allocator.nextFit(112);
    allocator.printMemory();

    return 0;
}
