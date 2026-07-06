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

	//6
	//14 123 323 321 421 535

	int main() {
		FILE *fp;
		freopen_s(&fp, "input.txt", "r", stdin);
		freopen_s(&fp, "output.txt", "w", stdout);
		int n = 0;
		cin >> n;
		vector<vector<int>> dp(10, vector<int>(10, 0));
		vector<string> v(n);
		string s;
		for (int i = 0; i < n; i++) {
			cin >> s;
			v[i] = s;
		}
		for (int i = n - 1; i >= 0; i--) {
			string temp = v[i];
			int first = temp[0] - '0';
			int last = temp[temp.size() - 1] - '0';
			int len = temp.size();	
			for (int j = 0; j <= 9; j++) {
				if (dp[last][j]) dp[first][j] = max(dp[first][j], dp[last][j] + len);
			}
			dp[first][last] = max(dp[first][last], len);
		}
		int ans = -1;
		for (int i = 0; i < 10; i++) {
					int res = dp[i][i];
					if (res > ans) {
						ans = res;
					}
		}
		cout << ans;
	}
