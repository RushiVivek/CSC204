#include <bits/stdc++.h>
using namespace std;

int n;

pair<double, double> rr(vector<vector<int> > a, int quantum) {
	int t = 0;
	queue<int> Q;
	vector<bool> visit(n);

	for (int i = 0; i < n; ++i) {
		a[i][2] = a[i][1];
	}

	while (1) {
		bool fl = 1;
		for (int i = 0; i < n; ++i) {
			if (a[i][0] <= t && !visit[i] && a[i][2] > 0) {
				Q.push(i);
				visit[i] = 1;
			}
		}

		if (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			fl = 0;

			if (a[curr][2] <= quantum) {
				t += a[curr][2];
				a[curr][2] = 0;
				a[curr][3] = t;
			} else {
				t += quantum;
				a[curr][2] -= quantum;
			}

			for (int i = 0; i < n; ++i) {
				if (a[i][0] <= t && !visit[i] && a[i][2] > 0) {
					Q.push(i);
					visit[i] = 1;
				}
			}
			if (a[curr][2] > 0) {
				Q.push(curr);
			}
		} else {
			++t;
		}
		if (fl && Q.empty()) break;
	}

	for (int i = 0; i < n; ++i) {
		a[i][4] = a[i][3] - a[i][0];
		a[i][5] = a[i][4] - a[i][1];
	}

	double at = 0, aw = 0;

	for (int i = 0; i < n; ++i) {
		at += a[i][4];
		aw += a[i][5];
	}
	at = at/n;
	aw = aw/n;
	return make_pair(at, aw);
}
pair<double, double> ljf(vector<vector<int> > a) {
	int t;
	int comp;
	t = comp = 0;
	vector<bool> completed(n);

	while (comp != n) {
		int ind = -1, bur = -1;
		for (int i = 0; i < n; ++i) {
			if (a[i][0] <= t && !completed[i] && a[i][1] > bur) {
				bur = a[i][1];
				ind = i;
			}
		}

		if (ind != -1) {
			t += a[ind][1];
			a[ind][3] = t;
			completed[ind] = 1;
			++comp;
		} else {
			++t;
		}
	}

	for (int i = 0; i < n; ++i) {
		a[i][4] = a[i][3] - a[i][0];
		a[i][5] = a[i][4] - a[i][1];
	}

	double at = 0, aw = 0;

	for (int i = 0; i < n; ++i) {
		at += a[i][4];
		aw += a[i][5];
	}

	at /= n;
	aw /= n;

	return make_pair(at, aw);
}
pair<double, double> lrtf(vector<vector<int> > a) {
	int t = 0, comp = 0;

}

int main() {
	cout << "Enter the number of processes: ";
	cin >> n;
	vector<vector<int> > a(n, vector<int>(6));
	for (int i = 0; i < n; ++i) {
		cout << "For P" << i << " :\n";
		cout << "Enter arrival time: ";
		cin >> a[i][0];
		cout << "Enter burst time: ";
		cin >> a[i][1];
	}

	cout << "Enter time quantum for round robin: ";
	int quantum;
	cin >> quantum;

	pair<double, double> rr_ans, ljf_ans, lrtf_ans;

	rr_ans = rr(a, quantum);
	ljf_ans = ljf(a);
	lrtf_ans = rr(a, quantum);

	cout << "Round Robin:\nAverage Turnaround Time = " << rr_ans.first << "\nAverage Waiting Time = " << rr_ans.second << "\n";
	cout << "LJF:\nAverage Turnaround Time = " << ljf_ans.first << "\nAverage Waiting Time = " << ljf_ans.second << "\n";
	cout << "LRTF:\nAverage Turnaround Time = " << lrtf_ans.first << "\nAverage Waiting Time = " << lrtf_ans.second << "\n";

	return 0;
}
