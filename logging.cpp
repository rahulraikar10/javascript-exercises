#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <array>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

// 📋 Problem Statement
// A logging robot starts at position 0 on a road of length N and must reach position N, chopping every tree along the way.

// Robot rules:

// The robot may move forward or backward; moving 1 unit takes 1 minute.
// Chopping and loading a tree takes 1 minute.
// All trees must be chopped exactly once.
// The global sequence of loaded trees must be non-increasing in length — each tree loaded must have length ≤ the previously loaded tree.
// At a position with trees on both sides, both may be chopped without moving, in	 either order, as long as the non-increasing constraint is satisfied.
// The robot has unlimited carrying capacity.

// Road rules:

// The road consists of integer positions 0 through N.
// At each position 1 through N-1, there is at most one tree on the left side and at most one tree on the right side.
// Positions 0 and N have no trees.
// There is at least one tree on the road.

// Find the minimum total time in minutes (movement + chopping) for the robot to chop all trees and stop at position N.

// Input
// N
// L[1] R[1]
// L[2] R[2]
// ...
// L[N-1] R[N-1]
// Each line i gives the left and right tree lengths at position i. A value of 0 means no tree on that side.
// 📥 Sample Input
// STDIN

// 5
// 0 0
// 0 2
// 0 3
// 1 2
// 0 0

// 📤 Sample Output
// STDOUT

// 11

using namespace std;
typedef long long ll;
vector<int> leftPos;
vector<int> rightPos;
vector<int> cost;
int n;
vector<vector<int>> dp;
int f(int len, int pos) {
	if (len == 0) return n - pos;
	if (dp[len][pos] != -1) {
		return dp[len][pos];
	}
	int goLeft = abs(pos - leftPos[len]) + cost[len] + f(len - 1, rightPos[len]);
	int goRight = abs(pos - rightPos[len]) + cost[len] + f(len - 1, leftPos[len]);
	return dp[len][pos] = min(goLeft, goRight);
}


int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	cin >> n;
	int maxm = 0;
	int l, r;
	map<int, vector<int>> mpp;
	for (int i = 0; i < n; i++) {
		cin >> l >> r;
		if (l) mpp[l].push_back(i);
		if (r) mpp[r].push_back(i);
		maxm = max(maxm, l);
		maxm = max(maxm, r);
	}
	leftPos.assign(maxm + 1, 0);
	rightPos.assign(maxm + 1, 0);
	cost.assign(maxm + 1, 0);
	for (auto &it : mpp) {
		int len = it.first;
		vector<int> v = it.second;
		sort(v.begin(), v.end());
		leftPos[len] = v.front();
		rightPos[len] = v.back();
		cost[len] = (rightPos[len] - leftPos[len]) + v.size();
	}

	    // Handle missing lengths
    for (int len = 1; len <= maxm; len++)
    {
        if (!mpp.count(len))
        {
            leftPos[len] = leftPos[len - 1];
            rightPos[len] = rightPos[len - 1];
            cost[len] = 0;
        }
    }

	dp.assign(maxm + 1, vector<int>(n + 1, -1));
	cout << f(maxm, 0); //start from max length and position ZERO
}
