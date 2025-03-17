#include <bits/stdc++.h>
using namespace std;

int n;

pair<double, double> fcfs(vector<vector<int> > a) {
	vector<int> c(n), w(n), t(n);
	sort(a.begin(), a.end());
	c[0] = a[0][1] + a[0][0];
	t[0] = a[0][1];
	w[0] = 0;
	for (int i = 1; i < n; ++i) {
		if (c[i-1] < a[i][0]) {
			c[i] = a[i][0] + a[i][0];
		} else {
			c[i] = c[i-1] + a[i][0];
		}
		t[i] = c[i] - a[i][0];
		w[i] = t[i] - a[i][1];
	}
	for (int i = n-1; i > 0; --i) {
		t[i-1] += t[i];
		w[i-1] += w[i];
	}
	double at, aw;
	at = aw = n;
	at = t[0]/at;
	aw = w[0]/aw;
	return make_pair(at, aw);
}
pair<double, double> sjf(vector<vector<int> > a) {
	sort(a.begin(), a.end());
	multiset<pair<int, int> > Q;
	vector<int> c(n), t(n), w(n);
	w[0] = 0;
	t[0] = a[0][1];
	c[0] = a[0][0] + a[0][1];
	int i = 0;
	while (i < n) {
		for (int j = i+1; j < n; ++j) {
			if (a[j][0] > c[i]) break;
			Q.insert(make_pair(a[j][1], a[j][0]);
		}
		++i;
		if (Q.empty()) {
			Q.insert(make_pair(a[i+1][1], a[i+1][0]));
		}
		auto st = *Q.begin();
		if (c[i-1] < st.second) {
			c[i] = st.second + st.first;
		} else {
			c[i] = c[i-1] + st.first;
		}
		Q.erase(Q.begin);
}
pair<double, double> srtf(vector<vector<int> > a);
pair<double, double> prior(vector<vector<int> > a);

int main() {
	cout << "Enter the number of processes: ";
	cin >> n;
	vector<vector<int> > a(n, vector<int>(3));
	for (int i = 0; i < n; ++i) {
		cout << "For P" << i << " :\n";
		cout << "Enter arrival time: ";
		cin >> a[i][0];
		cout << "Enter burst time: ";
		cin >> a[i][1];
		cout << "Enter priority: ";
		cin >> a[i][2];
	}

	pair<double, double> fcfs_ans, sjf_ans, srtf_ans, prior_ans;

	fcfs_ans = fcfs(a);
	sjf_ans = fcfs(a);
	srtf_ans = fcfs(a);
	prior_ans = fcfs(a);

	cout << "FCFS:\nAverage Turnaround Time = " << fcfs_ans.first << "\nAverage Waiting Time = " << fcfs_ans.second << "\n";
	cout << "SJF:\nAverage Turnaround Time = " << sjf_ans.first << "\nAverage Waiting Time = " << sjf_ans.second << "\n";
	cout << "SRTF:\nAverage Turnaround Time = " << srtf_ans.first << "\nAverage Waiting Time = " << srtf_ans.second << "\n";
	cout << "Priority Based:\nAverage Turnaround Time = " << prior_ans.first << "\nAverage Waiting Time = " << prior_ans.second << "\n";

	return 0;
}
