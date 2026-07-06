#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <array>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

//Given an array, find the maximum absolute difference between the sums of two non - overlapping subarrays.One subarray maximises its sum, the other minimises its sum.
//
//Input:  n / arr[0..n - 1]
//	Output : Maximum absolute difference.
//	📥 Sample Input
//	STDIN
//
//	4
//	1 2 - 3 4
int n = 0;
vector<int> a;
void solve(vector<int> &left,vector<int> &right) {

	int cur = a[0];
	int best = a[0];
	left[0] = a[0];
	for (int i = 1; i < n; i++) {
		cur = max(a[i], a[i] + cur);   // pay attention to this part, its NOT cur = max(cur,a[i]+cut)
		best = max(best, cur);
		left[i] = best;
	}
	cur = a[n - 1];
	best = a[n - 1];
	right[n - 1] = a[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		cur = max(a[i], a[i] + cur);
		best = max(cur, best);
		right[i] = best;
	}
}

int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	cin >> n;
	a.assign(n, 0);
	int ans = INT_MIN;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> lMin, rMin, rMax, lMax;
	lMin.assign(n, 0);
	rMin.assign(n, 0);
	lMax.assign(n, 0);
	rMax.assign(n, 0);
	solve(lMax,rMax);
	for (int i = 0; i < n; i++) {
		a[i] = -a[i];
	}
	solve(lMin, rMin);
	for (int i = 0; i < n; i++) {
		lMin[i] = -lMin[i];
		rMin[i] = -rMin[i];
	}
	for (int i = 0; i < n-1; i++) {
		int a1 = lMax[i];
		int a2 = rMin[i + 1];
		int diff1 = abs(a1 - a2);
		int a3 = lMin[i];
		int a4 = rMax[i + 1];
		int diff2 = abs(a3 - a4);
		int maxDiff = max(diff1, diff2);
		ans = max(ans, maxDiff);
	}
	cout << ans;
}
