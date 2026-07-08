/* Given N tiles each with (width, height), select exactly K tiles to minimize the maximum difference between any two selected tiles. Difference between tiles = max(|w1-w2|, |h1-h2|).

Input:  n k / w1 h1 / w2 h2 / ...
Output: ans
📥 Sample Input
STDIN

4 3
1 5
3 3
4 4
6 2

📤 Sample Output
STDOUT

3
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

ll n, k;
vector<pair<ll, ll>> v;

//windowed checking of the mid.

bool check(ll mid) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		while (j < i && (v[i].first - v[j].first > mid)) j++;
		if (i - j + 1 >= k) {
			vector<int> h;
			for (int idx = j; idx <= i; idx++) h.push_back(v[idx].second);
			sort(h.begin(), h.end());
			for (int i = 0; i + k - 1 < (int)h.size(); i++)
				if (h[i + k - 1] - h[i] <= mid) return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> k;
	v.resize(n);

	for (int i = 0; i < n; i++) 
		cin >> v[i].first >> v[i].second;
	sort(v.begin(), v.end()); //sort acc to widths
	ll lo = 0, hi = 1e9, ans = hi;
    
	while (lo <= hi) {
		ll mid = lo + (hi - lo) / 2;
		if (check(mid)) {
			ans = mid;
			hi = mid - 1;
		}
		else {
			lo = mid + 1;
		}
	}
	cout << ans << "\n";
}