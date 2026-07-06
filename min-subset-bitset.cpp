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

int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	int  n = 0;
	cin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		v.push_back(t);
	}
	int total = 0;
	for (int i = 0; i < n; i++) {
		total += v[i];
	}
	bitset<100001> dp;
	dp[0] = 1;
	int best = -1;
	for (auto x : v) dp |= (dp << x);
	for (int s = total / 2; s >= 0; s--) {
		if (dp[s]) {
			best = s;
			break;
		}
	}
	cout << abs(2 * best - total);
}
