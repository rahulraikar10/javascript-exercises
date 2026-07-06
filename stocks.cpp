#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <array>
#include<queue>
#include <set>
#include<map>
#include <algorithm>

//Initial stock A[i] and daily inflow B[i] for each item.Each day : inflow arrives, you may export one item(set stock to 0), report total stock.Find minimum days so total stock ≤ K.Return - 1 if impossible.
//
//Input : T / n K / s1 b1 / s2 b2 / ...
//	Output : ans
//	📥 Sample Input
//	STDIN
//
//	1
//	3 5
//	5 2
//	3 1
//	2 1

using namespace std;
using namespace std;
typedef long long ll;
ll n, K;
vector<pair<ll, ll>> v;
vector<vector<ll>> dp;
ll maxDay;

ll solve(ll idx, ll day)
{
	if (idx == n || day > maxDay)
		return 0;

	if (dp[idx][day] != -1)
		return dp[idx][day];

	// Don't remove this item
	ll skip = solve(idx + 1, day);

	// Remove this item on 'day'
	ll take = v[idx].second + day * v[idx].first
		+ solve(idx + 1, day + 1);

	return dp[idx][day] = max(skip, take);
}

bool possible(ll days)
{
	maxDay = days;

	ll total = 0;
	for (int i = 0; i < n; i++)
		total += v[i].second + days * v[i].first;

	dp.assign(n + 1, vector<ll>(days + 2, -1)); //safety check

	ll removed = solve(0, 1);

	return total - removed <= K;
}


int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	int T;
	cin >> T;

	while (T--)
	{
		cin >> n >> K;

		v.clear();

		for (int i = 0; i < n; i++)
		{
			ll stock, inflow;
			cin >> stock >> inflow;
			v.push_back({ inflow, stock });
		}

		sort(v.begin(), v.end());

		ll ans = -1;

		for (ll d = 0; d <= n; d++)
		{
			if (possible(d))
			{
				ans = d;
				break;
			}
		}

		cout << ans << "\n";
	}
}
