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

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = LLONG_MIN / 2;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while (T--) {
        int n; ll K;
        cin >> n >> K;
        vector<pair<ll,ll>> v(n); // {B, A}
        ll asum = 0, bsum = 0;
        for (int i = 0; i < n; i++) {
            ll a, b; 
			cin >> a >> b;
            v[i] = {b, a};
            asum += a; bsum += b;
        }
        sort(v.begin(), v.end()); // ascending by B

        // dp[j] = max savings choosing exactly j items, ranked 1..j
        vector<ll> dp(n + 1, NEG);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = min(i + 1, n); j >= 1; j--) {
                if (dp[j - 1] == NEG) continue;
                ll cand = dp[j - 1] + v[i].second + (ll)j * v[i].first;  //old saving + A + j*B
                if (cand > dp[j]) dp[j] = cand;
            }
        }

        ll ans = -1;
        for (int d = 0; d <= n; d++) {
            ll total = asum + (ll)d * bsum;
            if (total - dp[d] <= K) { ans = d; break; }
        }
        cout << ans << "\n";
    }
}