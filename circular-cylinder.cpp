#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include<queue>
#include <set>
#include <algorithm>

//📋 Problem Statement
//Given a binary matrix where each row is treated as a circular cylinder(columns wrap left - to - right).For each row, find the distance to the nearest 1. Then, for each column, sum the distances across all rows.Find the column with the minimum total sum.
//
//Input:  A matrix a with M rows and N columns.
//	Output : Minimum column - sum of distances.
//
//	📥 Sample Input
//	STDIN
//
//	6 5
//	0 1 0 0 1
//	0 0 0 1 0
//	0 1 0 0 0
//	0 0 0 0 1
//	0 0 1 0 0
//	1 0 0 0 0
//
//	📤 Sample Output
//	STDOUT
//
//	4

using namespace std;
using namespace std;
typedef long long ll;

void bfs(vector<vector<int>> &a, vector<vector<int>> &dp) {
	int m = a.size();
	int n = a[0].size();
	for (int i = 0; i < m; i++) {
		queue<int> q;
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 1) {
				q.push(j);
			}
		}
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			int next = (node + 1) % n;
			int prev = (node - 1 + n) % n;
			if (dp[i][next] == INT_MAX) {
				dp[i][next] = dp[i][node] + 1;
				q.push(next);
			}
			if (dp[i][prev] == INT_MAX) {
				dp[i][prev] = dp[i][node] + 1;
				q.push(prev);
			}


		}
	}
}

int main() {
	int m, n;
	cin >> m >> n;
	vector<vector<int>> a(m, vector<int>(n, 0));
	vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 1) {
				dp[i][j] = 0;
			}
		}
	}
	bfs(a, dp);
	int ans = INT_MAX;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m; j++) {
			sum += dp[j][i];
		}
		ans = min(ans, sum);
	}
	cout << ans;
}