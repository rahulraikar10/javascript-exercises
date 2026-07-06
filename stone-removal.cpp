	#include <iostream>
	#include <vector>
	#include <bitset>
	#include <unordered_map>
	#include <cstdio>
	#include <array>
	#include <queue>
	#include <set>
	#include <map>
	#include <algorithm>
	using namespace std;

	// 	📋 Problem Statement
	// Sequence of stones 1..N. Removing stone i costs: a[i] if one neighbor remaining, b[i] if two neighbors remaining, 0 if no neighbors (last). Find minimum total cost to remove all stones.

	// Input:  n / a1..an / b1..bn
	// Output: ans
	// 📥 Sample Input
	// STDIN

	// 3
	// 4 5 6
	// 3 2 1

	// 📤 Sample Output
	// STDOUT

	// 2

	int main() {
		FILE *fp;
		freopen_s(&fp, "input.txt", "r", stdin);
		freopen_s(&fp, "output.txt", "w", stdout);
		int n = 0;
		cin >> n;
		vector<int> a(n);
		vector<int> b(n);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];

		vector < vector<int>> dp(n + 1, vector<int>(2, 0));

		dp[1][0] = 0;
		dp[1][1] = a[0];

		for (int i = 2; i <=n; i++) {
			dp[i][0] = min(dp[i - 1][0] + a[i - 1], dp[i - 1][1]);
			dp[i][1] = min(dp[i - 1][0] + b[i - 1], dp[i - 1][1] + a[i - 1]);
		}
		cout << dp[n][0];
	}
