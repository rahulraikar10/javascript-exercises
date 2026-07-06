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

// Array of garbage values at indices 0..N-1. Deploy a robot at any index (cost m), robot can only move right (i+1). Cost at any point = sum of uncleaned garbage remaining. Find minimum total cost.

// Input:  t / n m / g1..gn
// Output: ans
// 📥 Sample Input
// STDIN

// 1
// 5 2
// 3 1 4 1 5

// 📤 Sample Output
// STDOUT

// 8

	using namespace std;
	int n, m;
	int solve(vector<vector<int>> &dp,int ind,int lastRobot,vector<int> &v) {
		if (ind == n) return 0;
		if (dp[ind][lastRobot] != -1) return dp[ind][lastRobot];
		int usePrev = (ind - lastRobot)*v[ind] + solve(dp, ind + 1, lastRobot, v);
		int deployNew = m + solve(dp, ind + 1, ind, v);
		return dp[ind][lastRobot] = min(usePrev, deployNew);
	}
	int main() {
		FILE *fp;
		freopen_s(&fp, "input.txt", "r", stdin);
		freopen_s(&fp, "output.txt", "w", stdout);
		cin >> n >> m;
		vector<int> v(n);
		int first = -1;
		for (int i = 0; i < n; i++) {
			cin >> v[i];

		}
		for (int i = 0; i < n; i++)
			if (v[i]) {
				first = i;  
				break;
			}
		vector<vector<int >> dp(500,vector<int>(500,-1));
		cout << m+solve(dp,first + 1, first, v);

	}
