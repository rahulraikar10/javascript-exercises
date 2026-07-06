#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
using namespace std;
typedef long long ll;

// Caluclate T using binary search, int T = (ans*(ans + 1)) / 2;


//📋 Problem Statement
// N cars at positions on XY plane. Move all to destination (p,q) simultaneously. Drive k: must move exactly k steps. After T drives, total moves = 1+2+...+T. Find minimum T so all cars reach destination simultaneously. Return -1 if impossible.

// Input:  t / n / p q / x1 y1 / x2 y2 / ...
// Output: ans
// 📥 Sample Input
// STDIN

// 1
// 2 
// 1 1
// 2 3
// -4 1

// 📤 Sample Output
// STDOUT

// 5

int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {

		int n = 0;
		cin >> n;
		pair<int, int> dest;
		vector<pair<int, int>> pts(n);
		set<int> parity_set;
		int maxD = INT_MIN;
		cin >> dest.first >> dest.second;
		for (auto &p : pts) {
			cin >> p.first >> p.second;
			int d = abs(p.first - dest.first) + abs(p.second - dest.second);
			parity_set.insert(d % 2);
			maxD = max(maxD, d);
		}
		if (parity_set.size() > 1) {
			cout << -1;
			continue;
		}
		int parity = *parity_set.begin();
		int low = 0;
		
		int high = sqrtl(2 * maxD) + 2;
		int ans = high;
		while (low <= high) {
			int mid = (low + high) / 2;
			if ((mid*(mid + 1)) / 2 >= maxD) {
				ans = mid;
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		int S = (ans*(ans + 1)) / 2;
		if (S % 2 == parity) {
			cout << ans;
		}
		else if ( ((ans+1)*(ans+2) / 2 ) % 2 == parity){
		cout << ans + 1;
		}
		else {
			cout << ans + 2;
		}


	}
}