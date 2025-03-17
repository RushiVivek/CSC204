#include <bits/stdc++.h>
using namespace std;

int n, m;

void dfs(const vector<vector<int>>& adjlist, int u, vector<int>& disc, vector<int>& low,
                    stack<int>* st, vector<bool>& instack) {
    int time = 0;

    disc[u] = low[u] = ++time;
    st->push(u);
    instack[u] = true;

    for (auto i = adjlist[u].begin(); i != adjlist[u].end(); ++i) {
        int v = *i;

        if (disc[v] == -1) {
            dfs(adjlist, v, disc, low, st, instack);
            low[u] = min(low[u], low[v]);
        }

        else if (instack[v])
            low[u] = min(low[u], disc[v]);
    }

    int w = 0;
    if (low[u] == disc[u]) {
        while (st->top() != u) {
            w = st->top();
            cout << w << " ";
            instack[w] = false;
            st->pop();
        }
        w = st->top();
        cout << w << "\n";
        instack[w] = false;
        st->pop();
    }
}

void SCC(const vector<vector<int>>& adjlist) {
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    vector<bool> instack(n, false);
    stack<int> *st = new stack<int>();

    for (int i = 0; i < n; i++)
        if (disc[i] == -1)
            dfs(adjlist, i, disc, low, st, instack);
}

int main() {
    cout << "Enter the number of vertices: ";
    cin >> n;
    vector<vector<int>> adjlist(n);
    cout << "Enter the number of edges: ";
    cin >> m;
    cout << "Enter the edges:\n";

    for (int i = 0; i < m; ++i) {
        int u, v;
        cout << ": ";
        cin >> u >> v;
        adjlist[u].push_back(v);
    }

    SCC(adjlist);

    return 0;
}
